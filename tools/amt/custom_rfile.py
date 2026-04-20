


class CustomRegisterFile(DefaultRegisterFile):
    def ev_set_stat0(self):
        self.data['cmdstat'] = self.data['cmdstat'] | 0x1

    def do_reg_write(self,r,v_in):
        # Inherit previous behavior
        v = DefaultRegisterFile.do_reg_write(self,r,v_in)

        if r == 'r5' and ((v_in & 0x1) == 0x1):
            # Clear cmdstat[0]:
            self.data['cmdstat'] |= 0x0
            # Schedule a set of cmdstat[0] in 10 instructions:
            self.add_event(self.emulator.ic+10,self.ev_set_stat0)

        return v
