#include <stdio.h>

void errlog0_proc(unsigned long int errlog0);
void main_read_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void main_write_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void shm_read_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void shm_write_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void control_bus_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void pcie_bus_errlog134_proc(unsigned long int errlog1, unsigned long int errlog3, unsigned long int errlog4);
void errlog56_proc(int group_num, unsigned long int errlog5 , unsigned long long int errlog6);

int main()
{
    int group_num, exit;

    while(1){
        printf("==== Rebel NOC Error Logger Group List ================================\n");
				printf("1) Main Bus Read   \n");
				printf("2) Main Bus Write  \n");
				printf("3) SHM  Bus Read   \n");
				printf("4) SHM	Bus Write  \n");
				printf("5) Control Bus     \n");
				printf("6) PCIE Bus        \n");
        printf("Select group : ");
        scanf("%d",&group_num);

        int groupselect_done=1;
        while(groupselect_done){
            if(group_num!=1 && group_num!=2 && group_num!=3 && group_num!=4 && group_num!=3 && group_num!=4 && group_num!=5 && group_num!=6){
                printf("Error : Please, select group again!!! (1~6)\n");
                printf("Select group : ");
                scanf("%d",&group_num);
            }
            else{
                groupselect_done=0;
            }
        }

        unsigned long int errlog0, errlog1, errlog3, errlog4, errlog5, errlog6;
        int ok, configuration_done=1;

        while(configuration_done){
            printf("=====Example==========================================\n");
            printf("Errorlog0 : 80030600 or 0x80030600\n");
            printf("======================================================\n");
            printf("Errorlog0 (0x14) : ");
            scanf("%x",&errlog0);
            printf("Errorlog1 (0x18) : ");
            scanf("%x",&errlog1);
            printf("Errorlog3 (0x20) : ");
            scanf("%x",&errlog3);
            printf("Errorlog4 (0x24) : ");
            scanf("%x",&errlog4);
            printf("Errorlog5 (0x28) : ");
            scanf("%x",&errlog5);
						printf("Errorlog6 (0x2C) : ");
            scanf("%llx",&errlog6);
            printf("Are all configurations correct? 1) Yes 2) No\n");
            scanf("%d",&ok);
            if(ok!=1){
                printf("======================================================\n");
                printf("Please, retry!!!\n");
            }else{
                configuration_done=0;
                break;
            }
        }
        errlog0_proc(errlog0);
        if(group_num == 1)
            main_read_errlog134_proc(errlog1,errlog3,errlog4);
        else if(group_num == 2)
            main_write_errlog134_proc(errlog1,errlog3,errlog4);
        else if(group_num == 3)
            shm_read_errlog134_proc(errlog1,errlog3,errlog4);
        else if(group_num == 4)
            shm_read_errlog134_proc(errlog1,errlog3,errlog4);
        else if(group_num == 5)
            control_bus_errlog134_proc(errlog1,errlog3,errlog4);
        else if(group_num == 6)
            pcie_bus_errlog134_proc(errlog1,errlog3,errlog4);
        errlog56_proc(group_num,errlog5, errlog6);
        printf("========= End ========================================\n");
        printf("##### Continue? 1) Yes 2) No\n");
        scanf("%d",&exit);
        if(exit != 1) return 1;
    }
}

void errlog0_proc(unsigned long int errlog0){
    unsigned long int Lock, Opc, ErrCode, Len1, Format;
    char ErrCode_print[7][10] = {"SLV", "DEC", "UNS","DISC", "SEC", "HIDE", "TMO"};
    char Opc_print[8][10] = {"RD", "RDW", "RDEX", "RDLK", "WR", "WRW", "WREX", "WRLK"};
    Format  = (errlog0 >> 31) & 0x1;
    Len1    = (errlog0 >> 16) & 0x7f;
    ErrCode = (errlog0 >> 8 ) & 0x7;
    Opc     = (errlog0 >> 1 ) & 0xf;
    Lock    = (errlog0      ) & 0x1;
    printf("========= ErrLog0 ====================================\n");
    printf("Format       : 0x%x\n",Format);
    printf("Len1         : 0x%x (%d Byte)\n",Len1,Len1+1);
    printf("ErrCode      : 0x%x (%s)\n" ,ErrCode,ErrCode_print[ErrCode]);
    printf("Opc          : 0x%x (%s)\n" ,Opc,Opc_print[Opc]);
    printf("Lock         : 0x%x\n",Lock);
}

void errlog56_proc(int group_num, unsigned long int errlog5, unsigned long long int errlog6){
    unsigned long int Allocate, Bufferable, Instruction, Lookup, Modifiable,Nonsecured,Privileged, QoS;
		unsigned long long int User;
    if(group_num == 5){
        Allocate    = (errlog5 >> 11)  & 0x1;
        Bufferable  = (errlog5 >> 12 ) & 0x1;
        Instruction = (errlog5 >> 13 ) & 0x1;
				Lookup			= (errlog5 >> 14 ) & 0x1;
				Modifiable  = (errlog5 >> 15 ) & 0x1;
				Nonsecured  = (errlog5 >> 16 ) & 0x1; 
				Privileged  = (errlog5 >> 17 ) & 0x1;
				User 				= ((errlog6 & 0xffff) << 14) + ((errlog5 >> 18 ) & 0x2fff);
        printf("========= ErrLog5/6 ====================================\n");
        printf("Allocate    : 0x%x\n",Allocate    );
        printf("Bufferable  : 0x%x\n",Bufferable  );
        printf("Instruction : 0x%x\n",Instruction );
        printf("Lookup      : 0x%x\n",Lookup			);
        printf("Modifiable  : 0x%x\n",Modifiable  );
        printf("Nonsecured  : 0x%x\n",Nonsecured  );
        printf("Privileged  : 0x%x\n",Privileged  );
        printf("User        : 0x%llx\n",User        );
    }
    else if(group_num == 6){
        Allocate    = (errlog5 >> 12 ) & 0x1;
        Bufferable  = (errlog5 >> 13 ) & 0x1;
        Instruction = (errlog5 >> 14 ) & 0x1;
				Lookup			= (errlog5 >> 15 ) & 0x1;
				Modifiable  = (errlog5 >> 16 ) & 0x1;
				Nonsecured  = (errlog5 >> 17 ) & 0x1; 
				Privileged  = (errlog5 >> 18 ) & 0x1;
				QoS         = (errlog5 >> 19 ) & 0xf;
				User 				= (errlog5 >> 23 ) & 0x1;
        printf("========= ErrLog5/6 ====================================\n");
        printf("Allocate    : 0x%x\n",Allocate    );
        printf("Bufferable  : 0x%x\n",Bufferable  );
        printf("Instruction : 0x%x\n",Instruction );
        printf("Lookup      : 0x%x\n",Lookup			);
        printf("Modifiable  : 0x%x\n",Modifiable  );
        printf("Nonsecured  : 0x%x\n",Nonsecured  );
        printf("Privileged  : 0x%x\n",Privileged  );
        printf("QoS         : 0x%x\n",QoS        );
        printf("User        : 0x%x\n",User        );
    }
    else{
        printf("User Logging isn't supported for main & shm");
				//Qos    = (errlog5 >> 13) & 0xf;
        //Prot   = (errlog5 >> 10) & 0x7;
        //User   = (errlog5 >> 4 ) & 0x3f;
        //Cache  = (errlog5      ) & 0xf;        
        //printf("========= ErrLog5 ====================================\n");
        //printf("Qos          : 0x%x\n",Qos);
        //printf("Prot         : 0x%x\n",Prot);
        //printf("User         : 0x%x\n",User);
        //printf("Cache        : 0x%x\n",Cache);
    }
}








































































