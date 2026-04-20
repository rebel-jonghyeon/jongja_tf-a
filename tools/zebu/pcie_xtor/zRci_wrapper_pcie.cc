#include "zRci_wrapper_pcie.hh"
#include "zRci_xtor_global_var.hh"
#include "pcie_test.hh"

xtor_pcie_svs *pcie[10];
xtor_pcie_svs *rc_xtor	= NULL;
monitor_pcie_svs *pcie_monitor[10];
xtor_pcie_svs_tlp *tlp = NULL;

thread rcThread;
thread testThread;
bool rc_flush_cpl = false;
bool run_test_flag = false;
bool thread_exit = false;

std::mutex	run_test_Mutex;
std::mutex	data_Mutex;

// Random Stream -----------------------------------------------
#define RANDOM_TABLE_SIZE 1024*1024
class random_stream {
	private:
		uint8_t		table[RANDOM_TABLE_SIZE];
		uint8_t		addr_hash(uint64_t addr);
		const char*	identifier;
		bool		trace;

	public:
		uint64_t	index;
		void		generate(uint64_t addr, uint32_t bytes, void *buffer);
		bool		check(uint64_t addr, uint32_t bytes, void *buffer);
		random_stream(uint32_t seed,const char* identifier, bool trace);
};

random_stream::random_stream (uint32_t seed,const char* name, bool verbose) {
	uint32_t i;

	trace = verbose;
	identifier = name;
	index = 0;
	srandom(seed);
	for (i=0; i<RANDOM_TABLE_SIZE; ++i) {
		table[i] = random();
	}
}

uint8_t random_stream::addr_hash (uint64_t addr) {
	addr ^= (addr>>32);
	addr ^= (addr>>16);
	addr ^= (addr>>8);

	return addr;
}

void random_stream::generate (uint64_t addr, uint32_t bytes, void *buffer) {
	uint32_t i;
	if (trace) {printf("[-- STREAM %s --]Pushing Data @ = %llx, number of byte = %d\n", identifier, (unsigned long long) addr, bytes);}
	for (i=0; i<bytes; ++i) {
		*(((uint8_t *)buffer)+i) = table[index] ^ addr_hash(addr + i);
		index = (index + 1) & (RANDOM_TABLE_SIZE-1);
	}
}

bool random_stream::check (uint64_t addr, uint32_t bytes, void *buffer) {
	uint32_t i;
	bool ret = true;

	if (trace) {printf("[-- STREAM %s --]Popping Data @ = %llx, number of byte = %d\n", identifier, (unsigned long long) addr, bytes);}
	for (i=0; i<bytes; ++i) {
		if (*(((uint8_t *)buffer)+i) != (table[index] ^ addr_hash(addr + i))) {
			//printf("[-- STREAM %s --]Index%12lld Byte%llx Got %02x Wait %02x\n",
			//		identifier, (unsigned long long) index, (unsigned long long)(addr+i),
			//		*(((uint8_t *)buffer)+i),(table[index] ^ addr_hash(addr + i)));
			ret = false;
		}
		index = (index + 1) & (RANDOM_TABLE_SIZE-1);
	}
	return ret;
}

// PCIe gMem -----------------------------------------------
class pcie_memory_c {
	public:
		uint64_t address;
		uint32_t data;
};

struct cpl_tlp_info {
	uint32_t bytes;
	uint8_t tag;
	uint16_t reqid;
	uint8_t* data;
};

#define data_size (0x40000+10)
uint32_t _data[16384];
bool mem_busy = false;
int ex_error_cnt=0;
vector <pcie_memory_c> pcie_gMem;

void display_memory () {
	data_Mutex.lock();
	unsigned j=0;
	for (vector<pcie_memory_c>::iterator i = pcie_gMem.begin(); i != pcie_gMem.end(); i++, j++ ) {
		if ((i - 1)->address + 4 != i->address) {
			if ((j + 1) % 4 != 0) cout << endl;
			j = 0;
			cout << endl;
		}
		if (j % 4 == 0)
			printf ("%s %llx (%d) \t\t: ","pcie_gMem", (long long unsigned int)(i->address), j);
		cout << hex << setw(8) << i->data;
		cout << " ";
		if ((j + 1) % 4 == 0) cout << endl;
	}
	cout << endl;
	data_Mutex.unlock();
}

void update_gMem (uint64_t address, uint32_t* data, unsigned size_in_32bits) {
	data_Mutex.lock();
	//mem_obj will be populated and will be inserted
	pcie_memory_c mem_obj;

	//'it' iterator is a pointer for the memory 'pcie_memory'
	vector<pcie_memory_c>::iterator it = pcie_gMem.begin();

	pcie_gMem.reserve(size_in_32bits);
	int first_be = 0xf;
	int last_be  = 0xf;
	for (unsigned i = 0, j = 0; j < size_in_32bits; i=i+4, j++ ) {
		mem_obj.address = address + i;
		if (j == 0) {
		// First DW , Suppose Data = 0x12345678
		// 0xF = 1111 , 0x12345678
		// 0xE = 1110 , 0x123456
		// 0xC = 1100 , 0x1234
		// 0x8 = 1000 , 0x12
			switch (first_be) {
			case 0xF : mem_obj.data = data[j];				break;
			case 0xE : mem_obj.data = data[j] & 0xFFFFFF00;	break;
			case 0xC : mem_obj.data = data[j] & 0xFFFF0000;	break;
			case 0x8 : mem_obj.data = data[j] & 0xFF000000;	break;
		// default : error_cnt++ ; printf ("%s ERROR!! Invalid value of first_be = 0x%X\n",ep_or_rc, first_be);
			}
		} else if (j == size_in_32bits - 1 ) {
		//Last DW , Suppose Data = 0x12345678
		//0xF = 1111 , 0x12345678
		//0x7 = 0111 , 0x345678
		//0x3 = 0011 , 0x5678
		//0x1 = 0001 , 0x78
		//mem_obj.dat a = data[j]
			switch (last_be) {
			case 0xF : mem_obj.data = data[j];				break;
			case 0x7 : mem_obj.data = data[j] & 0xFFFFFF;	break;
			case 0x3 : mem_obj.data = data[j] & 0xFFFF;		break;
			case 0x1 : mem_obj.data = data[j] & 0xFF;		break;
			default : ex_error_cnt++ ; printf (" ERROR!! Invalid value of last_be = 0x%X\n",last_be);
			}
		} else {
			mem_obj.data = data[j];
		}
		it = pcie_gMem.begin() + j;
		while ((it->address < address + i) && (it != pcie_gMem.end() )) {
			it++;
		}
		//If memory address is same then we need to over-write it
		if (it->address  == address + i ) {
			pcie_gMem.erase(it);
			pcie_gMem.insert(it, mem_obj);
		} else if ((it->address > address + i) /*|| (it->address == 0)*/) {
			//if received addr is smaller then insert at front
			pcie_gMem.insert(it, mem_obj);
		} else {
			//if received addr is greater than existing in memory then append at end
			pcie_gMem.push_back(mem_obj);
		}
	}
	data_Mutex.unlock();
}

bool get_read_data_from_mem(uint32_t *read_data, uint64_t address, unsigned size) {
	data_Mutex.lock();
	bool read_addr_found = false;
	vector<pcie_memory_c>::iterator it;
	bool ret = true;

	for (it = pcie_gMem.begin(); it !=pcie_gMem.end(); it++) {
		if (it->address == address) {
			read_addr_found = true;
			break;
		}
	}

	if (read_addr_found) {
		for (unsigned i = 0; i < size; i++, it++) {
			read_data[i] = it->data;
			if (it == pcie_gMem.end() && (i < size)) {
				cout << "ERROR!! Address not found. Trying to access address = 0x" << hex << address + i << endl;
				ret = false;
			}
		}
	} else {
		cout << "ERROR!! Address not found. Trying to access address = 0x" << hex << address << endl;
		ret = false;
	}

	data_Mutex.unlock();
	return ret;
}

// Completion Request Keeping -----------------------------------------------
class cpl_request {
	public:
		uint32_t bytes_;
		pcie_cpl_status_t status_;
		random_stream *rs_;
		uint64_t addr_;
		TLPHeaderFields_t tlpHdr_;
		cpl_request(pcie_cpl_status_t status, uint16_t reqid=0, uint16_t cplid=0, uint16_t tag=0, uint64_t addr=0, uint32_t bytes=0, random_stream *rs = NULL);
};

cpl_request::cpl_request(pcie_cpl_status_t status, uint16_t reqid, uint16_t cplid, uint16_t tag, uint64_t addr, uint32_t bytes, random_stream *rs) {
	status_ = status;
	bytes_  = bytes;
	addr_	= addr;
	rs_	 = NULL;
	tlpHdr_.reqid=reqid;
	tlpHdr_.cplid = cplid;
	tlpHdr_.tag=tag;
}

// Completion Record Keeping -----------------------------------------------
class cpl_record {
	private:
		uint32_t		  bytes_;	// expected bytes
		pcie_cpl_status_t status_;	// expected status

		void *target_;			  // if non-NULL, copy data here
		random_stream *rs_;		 // checker
		uint64_t addr_;			 // otherwise, do a check based on this address

	public:
		cpl_record(uint32_t bytes, void *target);
		cpl_record(uint64_t addr, uint32_t bytes, random_stream *rs);
		cpl_record(pcie_cpl_status_t status=PCIE_CPL_SC);

		bool process_cpl(uint32_t bytes, void *buffer, pcie_cpl_status_t status);
};

cpl_record::cpl_record (uint32_t bytes, void *target) {
	assert(target);
	assert(bytes);

	bytes_ = bytes;
	status_ = PCIE_CPL_SC;
	target_ = target;
	rs_ = NULL;
	addr_ = 0;
}

cpl_record::cpl_record (uint64_t addr, uint32_t bytes, random_stream *rs) {
	bytes_ = bytes;
	status_ = PCIE_CPL_SC;
	target_ = NULL;
	rs_ = rs;
	addr_ = addr;
}

cpl_record::cpl_record (pcie_cpl_status_t status) {
	bytes_ = 0;
	status_ = status;
	target_ = NULL;
	rs_ = NULL;
	addr_ = 0;
}

bool cpl_record::process_cpl (uint32_t bytes, void *buffer, pcie_cpl_status_t status) {

	if (status_!=status) {
		fprintf(stderr,"Wrong status: should be %d, but is %d\n", status_, status);
		return false;
	}

	if (bytes_!=bytes) {
		fprintf(stderr,"Wrong bytes: should be %d, but is %d\n", bytes_, bytes);
		return false;
	}

	if (target_) {
		assert(buffer);
		memcpy((uint8_t*)target_, (uint8_t*)buffer, bytes);
		return true;
	} else if (bytes) {
		assert(buffer);
		return rs_->check(addr_, bytes, buffer);
	}

	return true;
}


//============================================================================
//===	Root Complex Testbench

//! [Declare a wrapper derived class]
class RC_DEVICE: public xtor_wrapper_pcie_svs {
	public:
		RC_DEVICE(uint32_t seed, pcie_tb_type type);
		uint32_t			_seed;
		uint32_t			_maxPayloadSize_rc;
		uint32_t			_maxReadReqSize_rc;
		uint32_t			_maxPayloadSize_ep;
		uint32_t			_maxReadReqSize_ep;
		random_stream	  *rootport_randRxPayload;
		random_stream	  *rootport_randTxPayload;

		bool				rootport_Shutdown;

		std::mutex		  RxCplMutex;
		cpl_record*		 RxCplTable[256];
		std::mutex		TxCplMutex;
		std::queue<cpl_request*>	TxCplQueue;

		void				pcie_configure();
		void				pcie_Cpl_cb (const paramsCpl_cb_t & params);
		void				pcie_Msg_cb (const paramsMsg_cb_t & params);
		void				pcie_MWr_cb (const paramsMwr_cb_t & params);
		void				pcie_MRd_cb (const paramsMrd_cb_t & p_);
		void				pcie_ide_init_cb (void* ctxt);
		void				pcie_test();
		uint32_t			pcie_readcfg(uint32_t addr, uint32_t nbBytes);
		void				pcie_writecfg(uint32_t addr, uint32_t nbBytes, uint32_t word);
		void				pcie_writemem(uint64_t addr, uint32_t bytes, void *buffer);
		void				pcie_readmem(uint64_t addr, uint32_t bytes);
		void				pcie_message(uint8_t route, uint8_t code, uint64_t addr, uint32_t bytes, void *buffer);
		void		pcie_BfmCfgWr(uint32_t addr, uint32_t nbBytes, uint32_t word);
		uint8_t			 _err_cnt;
};
//! [Declare a wrapper derived class]

RC_DEVICE::RC_DEVICE (uint32_t seed,pcie_tb_type type):xtor_wrapper_pcie_svs(type,false) {
	_seed					= seed;
	_maxPayloadSize_rc		= 128;
	_maxReadReqSize_rc		= _maxPayloadSize_rc;
	_maxPayloadSize_ep		= 128;
	_maxReadReqSize_ep		= _maxPayloadSize_ep;
	rootport_Shutdown		= false;
	rootport_randRxPayload	= new random_stream(0,"RxPayload",false);
	rootport_randTxPayload	= new random_stream(0,"TxPayload",false);
	_err_cnt				= 0;
}

// -----------------------------------------------
void RC_DEVICE::pcie_configure() {

	pcie_xtor()->setName(pcie_xtor()->getDriverInstanceName());
	pcie_xtor()->print("Configuring PCIe RC ...\n");

	pcie_xtor()->setConfigParam("PCIE_TIMING",		"1");
	pcie_xtor()->setConfigParam("PCIE_TARGETSPEED",	"5");
	pcie_xtor()->setConfigParam("XTOR_NB_RESET_DE_ASSERTED",	"1");
	pcie_xtor()->setConfigParam("PCIE_MAXPAYLOAD",	 "4096");
	pcie_xtor()->setConfigParam("PCIE_BAR0SIZE",	  (std::to_string(BAR0SizeF0_RC)).c_str());
	pcie_xtor()->setConfigParam("PCIE_BAR0TYPE",	  (std::to_string(BAR0TypeF0_RC)).c_str());
	pcie_xtor()->setConfigParam("PCIE_BAR1SIZE",	  (std::to_string(BAR1SizeF0_RC)).c_str());
	pcie_xtor()->setConfigParam("PCIE_BAR1TYPE",	  (std::to_string(BAR1TypeF0_RC)).c_str());

	pcie_xtor()->print("ACTIVATING HW IDE RC ...\n");
	pcie_xtor()->setConfigParam("PCIE_XTOR_IDE_HW_ENABLE", "true");
	pcie_xtor()->setConfigParam("PCIE_XTOR_CFG_IDE_ENABLE","true");
	//pcie_xtor()->setConfigParam("IDE_TX_KEY",DOWNSTREAM_KEY);
	//pcie_xtor()->setConfigParam("IDE_RX_KEY",UPSTREAM_KEY);

	pcie_xtor()->setDebugLevel(DEBUG_FULL);
}

// -----------------------------------------------
void RC_DEVICE::pcie_Cpl_cb (const paramsCpl_cb_t & p_) {

	uint32_t MsgCode;
	bool exp_cpl=false;
	bool cpl_check=false;

	pcie_rxtlp()->printTLP(Full);
	RxCplMutex.lock();
	exp_cpl=(RxCplTable[p_.tag] != NULL);
	if (exp_cpl) {
		cpl_check=((RxCplTable[p_.tag])->process_cpl(p_.bytes,p_.payload,p_.status));
		delete RxCplTable[p_.tag];
		RxCplTable[p_.tag] = NULL;
		RxCplMutex.unlock();
		//if (!cpl_check) {
		//  pcie_xtor()->error("Receiving BAD completion for tag [%d] [%d][%p][%d]--------\n",
		//					p_.tag,p_.bytes,p_.payload,p_.status);
		//  pcie_xtor()->print ( "Stopping Traffic  from EP (MSG [%x][%x][@%x])\n",0x4, 0x7f, 0);
		//  MsgCode=0xDEADDEAD;
		//  pcie_Msg(0x4, 0x7F, 0, 4, &MsgCode);
		//  exit (911);
		//}

	} else {
		RxCplMutex.unlock();
		pcie_xtor()->error("ERROR Receiving UNEXPECTED completion with [tag,byte,ptr,status] [%d][%d][%p][%d]--------\n",
				p_.tag,p_.bytes,p_.payload,p_.status);
		pcie_xtor()->print ( "Stopping Traffic  from EP (MSG [%x][%x][@%x])\n",0x4, 0x7f, 0);
		MsgCode=0xDEADDEAD;
		pcie_Msg(0x4, 0x7F, 0, 4, &MsgCode);
		exit (911);
	}
}

// -----------------------------------------------
void RC_DEVICE::pcie_Msg_cb (const paramsMsg_cb_t & p_) {

	if (p_.code==0x7f && p_.route==0x4 && p_.bytes == 0x4) {
		if (*((uint32_t*)p_.payload)==0xDEADDEAD) {
			pcie_xtor()->print("Stopping test after Vendor Msg Reception Code 0x%x 0x%x\n",p_.code,p_.route);
			rootport_Shutdown = true;
		}
	}
	pcie_rxtlp()->printTLP(Full);
}
// -----------------------------------------------
void RC_DEVICE::pcie_ide_init_cb (void* ctxt) {
	pcie_xtor()->print("IDE INIT Callback !!!!! !!!!! !!!!!\n");
}
// -----------------------------------------------
uint32_t RC_DEVICE::pcie_readcfg(uint32_t addr, uint32_t nbBytes) {
	uint32_t cfgrd_payload = 0;
	RxCplMutex.lock();
	RxCplTable[pcie_CfgRd(addr, nbBytes)] =  new cpl_record(nbBytes, &cfgrd_payload);
	RxCplMutex.unlock();
	pcie_wait_cpl_all();

	return cfgrd_payload;
}

void RC_DEVICE::pcie_writecfg (uint32_t addr, uint32_t nbBytes, uint32_t word) {
	RxCplMutex.lock();
	RxCplTable[pcie_CfgWr(addr, nbBytes, word)] = new cpl_record(PCIE_CPL_SC);
	RxCplMutex.unlock();
	pcie_wait_cpl_all();
}

//test
void RC_DEVICE::pcie_BfmCfgWr (uint32_t addr, uint32_t nbBytes, uint32_t word) {
	//RxCplMutex.lock();
	//RxCplTable[pcie_BfmCfgWr(addr, nbBytes, word)] = new cpl_record(PCIE_CPL_SC);
	pcie_BfmCfgWr(addr, nbBytes, word);
	//RxCplMutex.unlock();
	//pcie_wait_cpl_all();
}

void RC_DEVICE::pcie_writemem (uint64_t addr, uint32_t bytes, void *buffer) {
	pcie_MWr(addr, bytes, buffer);
}
void RC_DEVICE::pcie_readmem (uint64_t addr, uint32_t bytes) {
	RxCplMutex.lock();
	RxCplTable[pcie_MRd(addr, bytes)] = new cpl_record(addr, bytes, rootport_randRxPayload);
	RxCplMutex.unlock();
	pcie_wait_cpl_all();
}
void RC_DEVICE::pcie_message (uint8_t route, uint8_t code, uint64_t addr, uint32_t bytes, void *buffer) {
	pcie_Msg(route, code, addr, bytes, buffer);
}

void RC_DEVICE::pcie_MWr_cb (const paramsMwr_cb_t & p_) {
	uint64_t addr = p_.addr;
	uint32_t bytes = p_.bytes;
	uint16_t reqid = p_.reqid;
	uint8_t *payload = p_.payload;
	pcie_xtor()->print("RC Received MWR request of [%d] Bytes @ Address [0x%0*llx]\n", bytes, 11, addr);
	update_gMem(addr, (uint32_t*)payload, (unsigned)(bytes / 4));
	if (addr == PCIE_HOST_TC_ADDR) {
		run_test_Mutex.lock();
		run_test_flag = true;
		run_test_Mutex.unlock();
	}
}

void RC_DEVICE::pcie_MRd_cb (const paramsMrd_cb_t & p_) {
	uint64_t addr = p_.addr;
	uint32_t bytes = p_.bytes;
	uint8_t  tag = p_.tag;
	uint16_t reqid = p_.reqid;
	uint8_t* data;

	pcie_xtor()->print("RC Received MRD request of [%d] Bytes @ Address [0x%0*llx]\n", bytes, 11, addr);
	TxCplMutex.lock();
	if (bytes==0) {
		TxCplQueue.push(new cpl_request(PCIE_CPL_SC,reqid, 0x100,tag));
	} else {
		TxCplQueue.push(new cpl_request(PCIE_CPL_SC,reqid,0x100,tag,addr,bytes));
	}
	rc_flush_cpl = true;
	TxCplMutex.unlock();
}

// -----------------------------------------------
void RC_DEVICE::pcie_test() {

	uint16_t cmd_reg;
	uint32_t number_of_active_bar;
	bool	 bar_used[6*MAXFUNC];
	bool	 bar_is_io[6*MAXFUNC];
	uint64_t bar_base[6*MAXFUNC];
	uint64_t bar_limit[6*MAXFUNC];

	uint32_t MsgCode;

	rootport_Shutdown	= false;
	number_of_active_bar = 0;

	for (uint8_t i=0; i<6*MAXFUNC; ++i) {
		bar_used[i]  = false;
		bar_is_io[i] = false;
		bar_base[i]  = 0;
		bar_limit[i] = 0;
	}

	uint32_t bus_reg = 0;
	uint32_t bar_reg = 0;
	uint16_t cfg_reg;

	RxCplMutex.lock();
	for (uint32_t tag_index=0; tag_index<256; ++tag_index) {
		RxCplTable[tag_index]=NULL;
	}
	RxCplMutex.unlock();

	bus_reg = 0x00010100;
	pcie_BfmCfgWr((XTOR_PCIE_SVS_TYPE1_SECLATTIMERSUBBUSSECBUSPRIBUS), 4, bus_reg);

	bus_reg = 0x00130100;
	pcie_BfmCfgWr((XTOR_PCIE_SVS_TYPE1_PREFMEMLIMITPREFMEMBASE), 4, bus_reg); // 32bits,100.0000-13FF.FFFF

	// set MPS/MRRS for RC in DevCtrl Register
	pcie_xtor()->print("Set RC Max payload/Read Request --------- [%d/%d bytes]\n",_maxPayloadSize_rc,_maxReadReqSize_rc);
	pcie_BfmCfgRd(((pcie_xtor()->getCapPtr(pcie_cap_id))+0x8), &cfg_reg);
	cfg_reg &=~(0x7<<5);
	switch (_maxPayloadSize_rc) {
		case 128:  cfg_reg |= (0x0<<5); break;
		case 256:  cfg_reg |= (0x1<<5); break;
		case 512:  cfg_reg |= (0x2<<5); break;
		case 1024: cfg_reg |= (0x3<<5); break;
		case 2048: cfg_reg |= (0x4<<5); break;
		case 4096: cfg_reg |= (0x5<<5); break;
		default: assert(0); break;
	}
	cfg_reg &=~(0x7<<12);
	switch (_maxReadReqSize_rc) {
		case 128:  cfg_reg |= (0x0<<12); break;
		case 256:  cfg_reg |= (0x1<<12); break;
		case 512:  cfg_reg |= (0x2<<12); break;
		case 1024: cfg_reg |= (0x3<<12); break;
		case 2048: cfg_reg |= (0x4<<12); break;
		case 4096: cfg_reg |= (0x5<<12); break;
		default: assert(0); break;
	}
	pcie_BfmCfgWr(((pcie_xtor()->getCapPtr(pcie_cap_id))+0x8), 4, cfg_reg);

	if (pcie_xtor()->getDeviceType() != PCIE_SVS_ROOTPORT) {
		pcie_xtor()->print ( "Inconsistent Bus Configuration !!!!!!!!!!!!!!! ...\n");
		_err_cnt++;
		exit (911);
	}

	// Probe Hardware Function
	uint32_t VendorDevID	= 0 ;
	uint32_t SubVendorDevID = 0 ;

	for (uint8_t func_reg=0; func_reg<MAXFUNC; ++func_reg) {

		pcie_set_current_bdfn (1, 0, func_reg);
		pcie_set_current_tc (0);

		// make sure bus/dev number is properly latched
		// this write has no effect because register 0 is read-only
		RxCplMutex.lock();
		RxCplTable[pcie_CfgWr((XTOR_PCIE_SVS_TYPE0_DEVIDVENDID), 4, bar_reg)] = new cpl_record(PCIE_CPL_SC);
		RxCplMutex.unlock();
		pcie_wait_cpl_all();
		RxCplMutex.lock();
		RxCplTable[pcie_CfgRd(XTOR_PCIE_SVS_TYPE0_DEVIDVENDID, 4)] =  new cpl_record(4, &VendorDevID);
		RxCplMutex.unlock();
		pcie_wait_cpl_all();
		RxCplMutex.lock();
		RxCplTable[pcie_CfgRd(XTOR_PCIE_SVS_TYPE0_SUBSYSTEMIDVENDORID , 4)] =  new cpl_record(4, &SubVendorDevID);
		RxCplMutex.unlock();
		pcie_wait_cpl_all();
		pcie_xtor()->print("-------- Function %d Detected With Device/Vendor ID (%x)  SubDevice/SubVendor (%x)---------\n", func_reg,VendorDevID, SubVendorDevID);
		//if (VendorDevID!= 0xabcd5678) {
		//  pcie_xtor()->print("-------- ERROR on Device/Vendor ID (%x) (exp:%x)---------\n", func_reg,VendorDevID, 0xabcd5678);
		//  _err_cnt++;
		//  exit (911);
		//}
	}

	return;
}

// -----------------------------------------------
xtor_pcie_svs *rc1	= NULL;
RC_DEVICE* rc = NULL;
struct WrapperArgs {
	RC_DEVICE* rc;
};

struct WrapperArgs WArgs;

uint32_t rc_exitCode = 1;
uint32_t ep_exitCode = 1;

//============================================================================
//===  PCIe RC
//============================================================================
void rc_InitIde_callback (void * context) {

	xtor_pcie_svs* xtor=(xtor_pcie_svs*) context;
	xtor->print("[RC]:[%s()]: Executing Ide Init user's callback\n",__func__);
	xtor->dbgPrint(DEBUG_LOW,"I am here\n");
} // void rc_InitIde_callback (void * context)

void run_rc (void* ctxt, svBitVecVal* exit_code) {
	RC_DEVICE * rc = ((WrapperArgs*)(ctxt))->rc;
	rc->setDebugLevel(DEBUG_FULL);
	rc->pcie_start();
	rc->pcie_training();
	rc->pcie_configure();
}

// -----------------------------------------------
void check_rc_flush_cpl (void* ctxt, svBitVecVal* exit_code) {
	RC_DEVICE * rc = ((WrapperArgs*)(ctxt))->rc;
	cpl_request* cpl;
	while (1) {
		if(rc_flush_cpl) {
			printf ("\n#### PCIE RC flush cpl\n");
			rc->TxCplMutex.lock();
			while (!rc->TxCplQueue.empty()) {
				cpl = (rc->TxCplQueue.front());
				uint32_t data[cpl->bytes_/4];
				bool ret = get_read_data_from_mem(data, cpl->addr_, cpl->bytes_/4); // getting data from the global memory generated
				if (cpl->bytes_== 0 || ret == false) {
					rc->pcie_Cpl(cpl->tlpHdr_, 0, NULL, PCIE_CPL_SC);
				} else {
					rc->pcie_Cpl(cpl->tlpHdr_, cpl->bytes_, data, cpl->status_);
				}
				rc->TxCplQueue.pop();
			}
			rc_flush_cpl = false;
			rc->TxCplMutex.unlock();
			printf ("\n#### PCIE RC flush cpl done\n");
		}
		if (thread_exit) {
			break;
		}
	}
}

//============================================================================
//===  PCIe IDE
//============================================================================
void IDE_insert_key(xtor_pcie_svs* xtor, uint32_t is_tx, uint32_t idx, uint32_t key_dw[], uint32_t ifv_dw[])
{
	uint32_t data_reg = 0x0;
	uint32_t addr_reg = 0x0;
	uint32_t base;

	if (is_tx)
		base = 0;
	else
		base = XTOR_PCIE_SVS_IDE_BASE_AESHOST_RX;

	addr_reg = base + XTOR_PCIE_SVS_IDE_AES_STAT_ADDR;
	data_reg = xtor->PCIeXtorIdeAesHostCfgRead(addr_reg,0);  //prot=0, sel_cm=IO (default)
	xtor->print("IDE AesHost Tx Status @=0x%x rdata=0x%x ...\n", addr_reg, data_reg);

	// Writing Key
	addr_reg = base + XTOR_PCIE_SVS_IDE_AES_KEY_0_ADDR;
	for (uint8_t i = 0; i < 8; i++) {
		data_reg = key_dw[8 - (i + 1)];
		xtor->PCIeXtorIdeAesHostCfgWrite(addr_reg, data_reg);
		xtor->dbgPrint(DEBUG_LOW,"IDE AesHost TX KEY_%1d: @=0x%x,wdata=0x%x ...\n",i,addr_reg,data_reg);
		addr_reg = addr_reg + 4;
	}

	// Writing IV
	for (uint8_t i = 0; i < 2; i++) {
		data_reg = ifv_dw[2 - (i + 1)];
		xtor->PCIeXtorIdeAesHostCfgWrite(addr_reg, data_reg);
		if (i == 0) {
			xtor->dbgPrint(DEBUG_LOW,"IDE AesHost TX INITIAL_IV_LSW: @=0x%x,wdata=0x%x ...\n",addr_reg,data_reg);
		} else if (i == 1) {
			xtor->dbgPrint(DEBUG_LOW,"IDE AesHost TX INITIAL_IV_MSW: @=0x%x,wdata=0x%x ...\n",addr_reg,data_reg);
		}
		addr_reg = addr_reg + 4;
	}

	addr_reg = base + XTOR_PCIE_SVS_IDE_AES_CTRL_ADDR;
	data_reg = xtor->PCIeXtorIdeAesHostCfgRead(addr_reg);
	xtor->dbgPrint(DEBUG_LOW,"IDE AesHost @=0x%x rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg &= ~(0xFFFF);
	data_reg |= idx;
	xtor->PCIeXtorIdeAesHostCfgWrite(addr_reg, data_reg);
	xtor->dbgPrint(DEBUG_LOW,"IDE AesHost AES_CTRL: @=0x%x,wdata=0x%x ...\n",addr_reg,data_reg);

	data_reg = xtor->PCIeXtorIdeAesHostCfgRead(addr_reg);
	xtor->dbgPrint(DEBUG_LOW,"Check IDE AesHost @=0x%x rdata=0x%x ...\n",addr_reg,data_reg);

	// Check/Wait BUSY flag
	addr_reg = base + XTOR_PCIE_SVS_IDE_AES_STAT_ADDR;
	while(1) {
		data_reg = xtor->PCIeXtorIdeAesHostCfgRead(addr_reg);
		// xtor->dbgPrint(DEBUG_LOW,"IDE AesHost Tx Status @=0x%x rdata=0x%x ...\n", addr_reg, data_reg);
		if ((data_reg & 0x1) == 0){
			xtor->PCIeXtorIdeAesHostCfgWrite(addr_reg, 1);
			break;
		}
	}
	xtor->dbgPrint(DEBUG_LOW,"Key insert done!!!\n");
}

void ide_key_prog(xtor_pcie_svs* xtor, uint8_t is_tx, uint8_t ss, uint8_t kset,
				uint32_t key_dw[], uint32_t ifv_dw[])
{
	uint32_t index = ss + 3;
	if (kset)
		index += 6;

	IDE_insert_key(xtor, is_tx, index, key_dw, ifv_dw);
}

void ide_key_swap(xtor_pcie_svs* xtor, uint8_t kset) {
	uint32_t data_reg = 0x0;
	uint32_t addr_reg = 0x0;

	/* RX_LNK_KBIT_CFG */
	data_reg = xtor->PCIeXtorIdeHostCfgRead(addr_reg);
	if (kset) {
		addr_reg = 0x24;
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x0);
		addr_reg = 0x1c;
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x7);
	} else {
		addr_reg = 0x24;
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x7);
		addr_reg = 0x1c;
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x0);
	}

#if 0
	/* TX_LNK_KBIT_CFG */
	addr_reg = 0x1c;
	data_reg = xtor->PCIeXtorIdeAesHostCfgRead(addr_reg);
	if (data_reg == 0)
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x7);
	else
		xtor->PCIeXtorIdeHostCfgWrite (addr_reg, 0x0);
#endif
}


// # -----------------------------------------------------------
void enableIDE (xtor_pcie_svs* xtor) {
	uint32_t data_reg = 0x0;
	uint32_t addr_reg = 0x0;

	xtor->dbgPrint(DEBUG_LOW,"enable IDE\n");
#if 1
	// TX_LINK_TBIT_CFG
	// [438768] UVM_INFO (cdn_ps_axi_reg_adp) UVM_WRITE, addr = 'h0000001ff81d0010 (tx_link_tbit_cfg), data = 'h0000003f
	addr_reg = 0x10;
	data_reg = xtor->PCIeXtorIdeHostCfgRead(addr_reg);
	xtor->dbgPrint(DEBUG_LOW,"current Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg = 0x0000003f;
	xtor->PCIeXtorIdeHostCfgWrite (addr_reg,data_reg);
	xtor->dbgPrint(DEBUG_LOW,"IDE HostCfg Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg &= 0x0;
	addr_reg &= 0x0;

	// TX_SLT_TBIT1_CFG
	// [438988] UVM_INFO (cdn_ps_axi_reg_adp) UVM_WRITE, addr = 'h0000001ff81d0014 (tx_slt_tbit1_cfg), data = 'h0000003f
	addr_reg = 0x14;
	data_reg = xtor->PCIeXtorIdeHostCfgRead(addr_reg);
	xtor->dbgPrint(DEBUG_LOW,"current Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg = 0x0000003f;
	xtor->PCIeXtorIdeHostCfgWrite (addr_reg,data_reg);
	xtor->dbgPrint(DEBUG_LOW,"IDE HostCfg Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg &= 0x0;
	addr_reg &= 0x0;
#endif

	// ////////////////////////////////////////
	// IDE mode START by Enabling LINK STREAM
	// ////////////////////////////////////////
	// IDE_LINK_STREAM_CTRL_0
	// [492183] UVM_INFO (cdn_ps_axi_reg_adp) UVM_WRITE, addr = 'h0000001c00000438, data = 'h01000101
	addr_reg = XTOR_PCIE_SVS_IDE_EXT_CAP_HDR_ADDR + 0xC;
	data_reg = xtor->PCIeXtorIdeCapsCfgRead(addr_reg);
	xtor->dbgPrint(DEBUG_LOW,"current IDE Link Stream Ctrl 0  Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);
	data_reg = 0x01000001;  // enable link stream // Stream ID = 1
	xtor->PCIeXtorIdeCapsCfgWrite (addr_reg,data_reg);
	xtor->dbgPrint(DEBUG_LOW,"IDE Link Stream Ctrl 0  Reg @=0x%x,rdata=0x%x ...\n",addr_reg,data_reg);

	xtor->print("Enable link stream done..\n");
	xtor->print("[RC]:Init IDE Done.\n");
}

//============================================================================
//===  PCIe hot reset
//============================================================================
/**
 * void pcie_xtor_tb::initiate_exit_hotreset()
 * Brief initiate hot reset  through software  by setting secondry reset field in bridge control register.
 * invoked by RC XTOR only.
 */

void initiate_exit_hotreset(xtor_pcie_svs* xtor) {

	uint32_t rdata;
	// Iniatilizing Hot reset.to enter D0s uninitailized state.
	// setting secondry bus reset bit in  bridge control register.
	xtor->print("---- RC XTOR: initializing HOT reset by Setting Secondry bus reset field of bridge control register \n");
	rdata = xtor->PCIeXtorCfgRead(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE);
	xtor->print("---- RC XTOR: default value of Bridge Control register =%0x \n ",rdata);
	rdata |= 0x00400000;
	xtor->PCIeXtorCfgWrite(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE,rdata);

	rdata = xtor->PCIeXtorCfgRead(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE);
	xtor->print("---- RC XTOR: Write value of  Bridge Control register =%0x \n ",rdata);
	xtor->print("----RC XTOR: wait for LTSSM State =STATE_HOT_RESET");
	xtor->wait_for((Ltssm_state_t)STATE_HOT_RESET);

	xtor->print("----RC XTOR: LTSSM State =STATE_HOT_RESET\n");

	// disabling  secondry bus reset bit in  bridge control register.
	rdata = xtor->PCIeXtorCfgRead(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE);
	xtor->print("---- RC XTOR: default value of Bridge Control register =%0x \n ",rdata);
	rdata &= 0xffbfffff;
	xtor->PCIeXtorCfgWrite(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE,rdata);

	rdata = xtor->PCIeXtorCfgRead(XTOR_PCIE_SVS_TYPE1_BRIDGECTRLINTPININTLINE);
	xtor->print("---- RC XTOR: Write value of  Bridge Control register =%0x \n ",rdata);
	xtor->print("----RC XTOR: wait for LTSSM State =STATE_DETECT_QUIET");
	xtor->wait_for(STATE_DETECT_QUIET);
	xtor->print("----RC XTOR Entered detect Quiet \n");
	xtor->print("----RC XTOR Applying Hw reset\n");
	xtor->reqFor(hw_reset_n, true);
	xtor->runClk(10);
	xtor->reqFor(hw_reset_n, false);
	xtor->print("----RC XTOR cfg xtor after detect \n");
	xtor->initBFM();
}

//============================================================================
//===  PCIe post board init
//============================================================================
void zRci_pcie_post_board_init () {
	cerr << "#TB : Register PCIE Transactor..." << board << endl;
	//! [Create a wrapper derived instance]
	rc = new RC_DEVICE(0,PCIE_TB_RP);
	assert (rc!=NULL);
	//! [Create a wrapper derived instance]

	rc->pcie_init(XtorRuntimeZebuMode,"top.pcie_driver_rc");

	rc->setDebugLevel(DEBUG_FULL);
	rc->pcie_xtor()->registerInitIdeCB(rc_InitIde_callback, (void*)(rc->pcie_xtor()));
	monitor_pcie_svs::Register();
	for (int i=0; i<num_monitor_pcie_svs; i++) {
		pcie_monitor[i] = new monitor_pcie_svs("monitor_pcie_svs_core", inst_monitor_pcie_svs[i], xsched, runtime);
	}

}

//============================================================================
//===  PCIe monitor
//============================================================================
void Xtor_Pcie_analyzer_stop() {
	for (int i=0; i<num_monitor_pcie_svs; i++) {
		pcie_monitor[i]->analyzerStop();
	}
}

void Xtor_Pcie_analyzer_start() {
	for (int i=0; i<num_monitor_pcie_svs; i++) {
		pcie_monitor[i]->analyzerStart();
	}
}

//============================================================================
//===  PCIe cleanup
//============================================================================
void zRci_pcie_cleanup() {
	thread_exit = true;
	rcThread.join();
	testThread.join();
	rc = NULL;
	//for (int i=0; i<num_xtor_pcie_svs; i++) {
	//	pcie[i] = NULL;
	//}
}

//============================================================================
//===  PCIe IDE test sequence
//============================================================================
void send_doe_k_set_go(uint8_t is_tx, uint8_t ss, uint8_t kset)
{
	while(1) {
		uint32_t payload = rc->pcie_readcfg(0xdec, 4);
		if ((payload & 0x1) == 0)
			break;

		rc->pcie_xtor()->runClk(1000000);
	}

	rc->pcie_writecfg(0xdf0, 4, 0);
	rc->pcie_writecfg(0xdf0, 4, 4);
	rc->pcie_writecfg(0xdf0, 4, 0x400);
	rc->pcie_writecfg(0xdf0, 4, (((ss & 0xF) << 20) | ((kset & 0x1) << 16)) | ((is_tx & 0x1) << 17));

	rc->pcie_writecfg(0xde8, 4, 0x80000000);
}

void send_doe_key_prog(uint8_t is_tx, uint8_t ss, uint8_t kset,  uint32_t key_dw[], uint32_t ifv_dw[])
{
	while(1) {
		uint32_t payload = rc->pcie_readcfg(0xdec, 4);
		if ((payload & 0x1) == 0)
			break;

		rc->pcie_xtor()->runClk(1000000);
	}

	rc->pcie_writecfg(0xdf0, 4, 0);
	rc->pcie_writecfg(0xdf0, 4, 14);
	rc->pcie_writecfg(0xdf0, 4, 0x200);
	rc->pcie_writecfg(0xdf0, 4, (((ss & 0xF) << 20) | ((kset & 0x1) << 16)) | ((is_tx & 0x1) << 17));

	for(int i = 0; i < 8; i++) {
		rc->pcie_writecfg(0xdf0, 4, key_dw[i]);
	}

	for(int i = 0; i < 2; i++) {
		rc->pcie_writecfg(0xdf0, 4, ifv_dw[i]);
	}

	rc->pcie_writecfg(0xde8, 4, 0x80000000);
}

uint32_t doe_payload[65];

void read_doe_resp() {
	uint32_t len = 0, i;

	while(1) {
		doe_payload[0] = rc->pcie_readcfg(0xdec, 4);
		if (doe_payload[0] == 0x80000000)
			break;

		rc->pcie_xtor()->runClk(1000000);
	}

	doe_payload[1] = rc->pcie_readcfg(0xdf4, 4);
	rc->pcie_writecfg(0xdf4, 4, 0);

	doe_payload[2] = rc->pcie_readcfg(0xdf4, 4);
	len = doe_payload[2] - 2;
	rc->pcie_writecfg(0xdf4, 4, 0);

	for (i=0; i < len; i++) {
		doe_payload[3 + i] = rc->pcie_readcfg(0xdf4, 4);
		rc->pcie_writecfg(0xdf4, 4, 0);
	}

	printf("==============================\n");
	printf("DOE Status:%x\n", doe_payload[0]);
	printf("DW0:%x\n",doe_payload[1]);
	printf("DW1:%x\n",doe_payload[2]);
	for (i = 0; i < len; i++)
		printf("Data %d:%x\n",i, doe_payload[i + 3]);
	printf("==============================\n");
}

void update_key_dw(uint32_t key_dw[], uint32_t ifv_dw[])
{
	for (int i = 0; i < 8; i++) {
		key_dw[i] = key_dw[i] + i * 0x10;
	}
	for (int i = 0; i < 2; i++) {
		ifv_dw[i] = ifv_dw[i] + i * 0x10;
	}
}

void prepare_new_keys(uint8_t kset)
{
	uint8_t ss = 0;
	uint32_t key_dw[8] = {0,}, ifv_dw[2] = {0,};

	for (int i = 0; i < 8; i++) {
		key_dw[i] = 0x33330000 + i;
	}
	for (int i = 0; i < 2; i++) {
		ifv_dw[i] = 0x44440000 + i;
	}

	for (int i = 0; i < 3; i++) {
		update_key_dw(key_dw, ifv_dw);

		ss = i;
		ide_key_prog(rc->pcie_xtor(), 0, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(0, ss, kset, key_dw, ifv_dw);
		read_doe_resp();

		ide_key_prog(rc->pcie_xtor(), 1, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(1, ss, kset, key_dw, ifv_dw);
		read_doe_resp();
	}
}

void start_ide_kswap_test(uint8_t kset) {
	uint8_t ss = 0;

	/* Key set go*/
	for (int i = 0; i < 3; i++) {
		ss = i;
		send_doe_k_set_go(0, ss, kset);
		read_doe_resp();

		send_doe_k_set_go(1, ss, kset);
		if (i==2) {
			ide_key_swap(rc->pcie_xtor(), kset);
			rc->pcie_xtor()->runClk(1000000);
		}

		read_doe_resp();
	}

	if (kset) kset = 0;
	else kset = 1;
	prepare_new_keys(kset);
}

void insert_initial_keys()
{
	uint8_t ss = 0, kset = 0;
	uint32_t key_dw[6][8] =
		{{0x22222222, 0x22222222, 0x22222222, 0x22222222,
		  0x22222222, 0x22222222, 0x22222222, 0x22222222},
		 {0x66666666, 0x66666666, 0x66666666, 0x66666666,
		  0x66666666, 0x66666666, 0x66666666, 0x66666666},
		 {0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa,
		  0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa},
		 {0x11111111, 0x11111111, 0x11111111, 0x11111111,
		  0x11111111, 0x11111111, 0x11111111, 0x11111111},
		 {0x55555555, 0x55555555, 0x55555555, 0x55555555,
		  0x55555555, 0x55555555, 0x55555555, 0x55555555},
		 {0x99999999, 0x99999999, 0x99999999, 0x99999999,
		  0x99999999, 0x99999999, 0x99999999, 0x99999999}};
	uint32_t ifv_dw[6][2] =
		{{0x44444444, 0x44444444},
		 {0x88888888, 0x88888888},
		 {0xcccccccc, 0xcccccccc},
		 {0x33333333, 0x33333333},
		 {0x77777777, 0x77777777},
		 {0xbbbbbbbb, 0xbbbbbbbb}};

	/* Initial Keys */
	for (int i = 0; i < 3; i++) {
		/* RX */
		ide_key_prog(rc->pcie_xtor(), 0, i, kset, key_dw[i], ifv_dw[i]);
		/* TX */
		ide_key_prog(rc->pcie_xtor(), 1, i, kset, key_dw[i+3], ifv_dw[i+3]);
	}
}

void start_ide_test() {

	uint8_t ss = 0, kset = 0;
	uint32_t key_dw[8] = {0,}, ifv_dw[2] = {0,};

	for (int i = 0; i < 8; i++) {
		key_dw[i] = 0x11110000 + i;
	}
	for (int i = 0; i < 2; i++) {
		ifv_dw[i] = 0x22220000 + i;
	}

	/* Initial Keys */
	kset = 0;
	for (int i = 0; i < 3; i++) {
		update_key_dw(key_dw, ifv_dw);

		ss = i;
		ide_key_prog(rc->pcie_xtor(), 0, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(0, ss, kset, key_dw, ifv_dw);
		read_doe_resp();

		ide_key_prog(rc->pcie_xtor(), 1, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(1, ss, kset, key_dw, ifv_dw);
		read_doe_resp();
	}

	/* Backup Keys */
	kset = 1;
	for (int i = 0; i < 3; i++) {
		update_key_dw(key_dw, ifv_dw);

		ss = i;
		ide_key_prog(rc->pcie_xtor(), 0, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(0, ss, kset, key_dw, ifv_dw);
		read_doe_resp();

		ide_key_prog(rc->pcie_xtor(), 1, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(1, ss, kset, key_dw, ifv_dw);
		read_doe_resp();
	}


	/* Key set go*/
	kset = 0;
	for (int i=0; i<3; i++) {
		ss = i;
		send_doe_k_set_go(0, ss, kset);
		read_doe_resp();

		send_doe_k_set_go(1, ss, kset);
		read_doe_resp();
	}

	enableIDE(rc->pcie_xtor());
}

//============================================================================
void run_test_doe()
{
	while(1) {
		uint32_t payload = rc->pcie_readcfg(0xdec, 4);
		if ((payload & 0x1) == 0)
			break;

		rc->pcie_xtor()->runClk(1000000);
	}

	rc->pcie_writecfg(0xdf0, 4, 0);
	rc->pcie_writecfg(0xdf0, 4, PCIE_DOE_TEST_LENGTH);
	rc->pcie_writecfg(0xdf0, 4, PCIE_DOE_TEST_PAYLOAD_0);
	rc->pcie_writecfg(0xdf0, 4, PCIE_DOE_TEST_PAYLOAD_1);

	rc->pcie_writecfg(0xde8, 4, 0x80000000);

	read_doe_resp();

	uint32_t payload = RESULT_FAIL;
	if ((doe_payload[3] == PCIE_DOE_TEST_PAYLOAD_0) &&
		(doe_payload[4] == PCIE_DOE_TEST_PAYLOAD_1)) {
		payload = RESULT_PASS;
	}

	update_gMem(PCIE_HOST_TC_RESULT_ADDR, &payload, 1);
}

void run_test_msix()
{
	uint32_t payload = RESULT_PASS;
	uint32_t data;
	uint32_t expected;
	int ret;

	for (int i = 0; i < 32; i++) {
		expected = PCIE_MSIX_TEST_MSG_DATA + i;
		ret = get_read_data_from_mem(&data, PCIE_MSIX_TEST_HOST_ADDRESS + i * 4, 1);
		if (ret == false || expected != data) {
			printf("expected :%x but %x\n", expected, data);
			payload = RESULT_FAIL;
			break;
		}
	}

	update_gMem(PCIE_HOST_TC_RESULT_ADDR, &payload, 1);
}

void check_run_test(void* ctxt, svBitVecVal* exit_code)
{
	while (1) {
		if(run_test_flag) {
			run_test_Mutex.lock();
			uint32_t tc;
			get_read_data_from_mem(&tc, PCIE_HOST_TC_ADDR, 1);
			printf("TEST CASE %x START\n",tc);
			switch (tc) {
			case TEST_ID_DOE:
				run_test_doe();
				break;
			case TEST_ID_MSIX:
				run_test_msix();
				break;
			defaut:
				break;
			}
			run_test_flag = false;
			run_test_Mutex.unlock();
		}
		if (thread_exit) {
			break;
		}
	}
}

//============================================================================
//===  PCIe zRci command
//===
//===	1. pcie_initbfm
//===		need to be done before using xtor_pcie_svs
//===	2. pcie_start_test
//============================================================================
void zRci_pcie_command (const string key, const string& value) {
	std::string ret_val_str = "UnknownCommand";
	printf("Processing command \"%s\"\n",key.c_str());

	std::vector<string> sep = split(value, ' ');

	if (strcmp(key.c_str(),"pcie_initbfm") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		rc->pcie_xtor()->config();
		rc->pcie_xtor()->initBFM();
		cerr << "initBFM DONE" << endl;
	}
	else if (strcmp(key.c_str(),"enableIDE") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		insert_initial_keys();
		enableIDE(rc->pcie_xtor());
		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_ide_start_test") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		start_ide_test();
		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_ide_start_kswap_test") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		if(sep.size() != 1){
			fprintf(stderr, "Wrong arguments num\n");
			return;
		}

		uint8_t kset = (uint8_t)std::stoul(sep[0],0,0);
		start_ide_kswap_test(kset);
		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_ide_key_swap") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		//ide_key_swap(rc->pcie_xtor());
		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_ide_key_prog") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		if(sep.size() != 13){
			fprintf(stderr, "Wrong arguments num\n");
			return;
		}
		uint8_t tx = (uint8_t)std::stoul(sep[0],0,0);
		uint8_t ss = (uint8_t)std::stoul(sep[1],0,0);
		uint8_t kset = (uint8_t)std::stoul(sep[2],0,0);
		uint32_t key_dw[8] = {0,}, ifv_dw[2] = {0,};

		for (int i = 0; i < 8; i++) {
			key_dw[i]=(uint32_t)std::stoul(sep[3+i],0,0);
		}
		for (int i = 0; i < 2; i++) {
			ifv_dw[i]=(uint32_t)std::stoul(sep[11+i],0,0);
		}

		ide_key_prog(rc->pcie_xtor(), tx, ss, kset, key_dw, ifv_dw);
		send_doe_key_prog(tx, ss, kset, key_dw, ifv_dw);

		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_ide_k_set_go") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		if(sep.size() != 3){
			fprintf(stderr, "Wrong arguments num\n");
			return;
		}
		uint8_t tx = (uint8_t)std::stoul(sep[0],0,0);
		uint8_t ss = (uint8_t)std::stoul(sep[1],0,0);
		uint8_t kset = (uint8_t)std::stoul(sep[2],0,0);

		send_doe_k_set_go(tx, ss, kset);

		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_read_doe_resp") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");

		read_doe_resp();

		ret_val_str = "OK";
	}
	else if (strcmp(key.c_str(),"pcie_start_test") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");

		WArgs = {rc};
		rcThread = std::thread(run_rc,(void*)(&WArgs),(svBitVecVal*)(&rc_exitCode));
		rcThread.join();

		for(int i = 0; i < 16384; i++) {
			if (i == 0) _data[i]=0x12345678;
			else if (i == 63) _data[i] = 0xCAFE0063;
			else if (i == 127) _data[i] = 0xCAFE0127;
			else if (i == 1023) _data[i] = 0xCAFE1023;
			else _data[i] = 0xFEEDD000 + i;
		}
		// Init XTOR memory
		for (int i = 0; i < 0x4000; i++) // 0x4000 * 4 = 0x10000
		{
			update_gMem(0x80000000 + (i * 4), &(_data[i]), 1);
		}
		uint32_t temp_payload[32] = {0,};
		update_gMem(PCIE_HOST_TC_ADDR, temp_payload, 2);
		update_gMem(PCIE_MSIX_TEST_HOST_ADDRESS, temp_payload, 32);

		rcThread = std::thread(check_rc_flush_cpl,(void*)(&WArgs),(svBitVecVal*)(&rc_exitCode));
		testThread = std::thread(check_run_test,(void*)(&WArgs),(svBitVecVal*)(&rc_exitCode));

		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_readcfg") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		if(sep.size() != 3){
			fprintf(stderr, "Wrong arguments num\n");
			return;
		}
		uint8_t func_num = (uint8_t)std::stoul(sep[0],0,0);
		uint32_t addr = (uint32_t)std::stoul(sep[1],0,0);
		uint32_t size = (uint32_t)std::stoul(sep[2],0,0);

		rc->pcie_set_current_bvfn(1, func_num);
		// uint32_t addr, uint32_t nbBytes, int dly = -1, int priority = 0
		rc->pcie_readcfg(addr, size);
		rc->pcie_set_current_bvfn(1, 0);

		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_writecfg") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		if(sep.size() != 4){
			fprintf(stderr, "Wrong arguments num\n");
			return;
		}
		uint8_t func_num = (uint8_t)std::stoul(sep[0],0,0);
		uint32_t addr = (uint32_t)std::stoul(sep[1],0,0);
		uint32_t size = (uint32_t)std::stoul(sep[2],0,0);
		uint32_t word = (uint32_t)std::stoul(sep[3],0,0);

		rc->pcie_set_current_bvfn(1, func_num);
		// uint32_t addr, uint32_t nbBytes, uint32_t word, int dly = -1, int priority = 0
		rc->pcie_writecfg(addr, size, word);
		rc->pcie_set_current_bvfn(1, 0);
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_bfmwritecfg") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		// uint32_t addr, uint32_t nbBytes, uint32_t word, int dly = -1, int priority = 0
		rc->pcie_BfmCfgWr((uint32_t)std::stoul(sep[0],0,16),(uint32_t)std::stoul(sep[1],0,16), (uint32_t)std::stoul(sep[2],0,16));
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_writemem") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		uint64_t addr = (uint64_t)std::stoul(sep[0],0,0);
		uint32_t size = (uint32_t)std::stoul(sep[1],0,0);
		uint32_t MWr_buffer[10];
		for (int i = 0; i < size/4; i++) {
			MWr_buffer[i]=(uint32_t)std::stoul(sep[2+i],0,0);
			printf("data:%x\n",MWr_buffer[i]);

		}
		// uint64_t addr, uint32_t bytes, void *buffer, bool contain_tlp_prfx = false, uint32_t tlp_prfx = 0, int dly = -1, int priority = 0
		rc->pcie_writemem(addr, size, MWr_buffer);
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_readmem") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		// uint64_t addr, uint32_t bytes, void *buffer, bool contain_tlp_prfx = false, uint32_t tlp_prfx = 0, int dly = -1, int priority = 0
		rc->pcie_readmem((uint64_t)std::stoul(sep[0],0,16),(uint32_t)std::stoul(sep[1],0,16));
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_message") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		uint32_t MsgCode=(uint32_t)std::stoul(sep[4],0,16);
		// uint8_t route, uint8_t code, uint64_t addr, uint32_t bytes = 0, void *buffer = NULL, int dly = -1, int priority = 0
		rc->pcie_message((uint8_t)std::stoul(sep[0],0,16),(uint8_t)std::stoul(sep[1],0,16),(uint64_t)std::stoul(sep[2],0,16),(uint32_t)std::stoul(sep[3],0,16), &MsgCode);

		ret_val_str = "OK";
	}
		else if(strcmp(key.c_str(),"pcie_display_memory") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		display_memory();
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_start_analyzer") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		Xtor_Pcie_analyzer_start();
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_stop_analyzer") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		Xtor_Pcie_analyzer_stop();
		ret_val_str = "OK";
	}
	else if(strcmp(key.c_str(),"pcie_hot_reset") == 0) {
		fprintf(stderr, "=========================================================\n");
		fprintf(stderr, "		  %s ...  \n", key.c_str());
		fprintf(stderr, "=========================================================\n");
		initiate_exit_hotreset(rc->pcie_xtor());
		ret_val_str = "OK";
	}
	//else if(strcmp(key.c_str(),"pcie_backdoor_read_memory") == 0) {
	//	fprintf(stderr, "=========================================================\n");
	//	fprintf(stderr, "		  %s ...  \n", key.c_str());
	//	fprintf(stderr, "=========================================================\n");
	//	get_read_data_from_mem((uint32_t)std::stoul(sep[0],0,16),(uint32_t)std::stoul(sep[1],0,16));
	//	ret_val_str = "OK";
	//}

	//else if(strcmp(key.c_str(),"pcie_backdoor_write_memory") == 0) {
	//	fprintf(stderr, "=========================================================\n");
	//	fprintf(stderr, "		  %s ...  \n", key.c_str());
	//	fprintf(stderr, "=========================================================\n");
	//	uint32_t data=(uint32_t)std::stoul(sep[1],0,16);
	//  update_gMem((uint64_t)std::stoul(sep[0],0,16),&data, 1);
	//	ret_val_str = "OK";
	//}
}
