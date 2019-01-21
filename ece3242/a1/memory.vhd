--------------------------------------------------------
-- SSimple Computer Architecture
--
-- memory 256*16
-- 8 bit address; 16 bit data
-- memory.vhd
--------------------------------------------------------

library	ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;   
use work.MP_lib.all;

entity memory is
port ( 	clock	: 	in std_logic;
		rst		: 	in std_logic;
		Mre		:	in std_logic;
		Mwe		:	in std_logic;
		address	:	in std_logic_vector(7 downto 0);
		data_in	:	in std_logic_vector(15 downto 0);
		data_out:	out std_logic_vector(15 downto 0)
);
end memory;

architecture behv of memory	 is			

type ram_type is array (0 to 255) of std_logic_vector(15 downto 0);
signal tmp_ram: ram_type;
begin
	write: process(clock, rst, Mre, address, data_in)
	begin				-- program to generate 10 fabonacci number	 
		if rst='1' then		
			tmp_ram <= (0 => x"3000",	   		-- R0 <- #0			mov R0, #0
						1 => x"3101",			-- R1 <- #1			mov R1, #1
						2 => x"3234",			-- R2 <- #52		mov R2, #52
						3 => x"3301",			-- R3 <- #1			mov R3, #1
						4 => x"1032",			-- M[50] <- R0 		mov M[50], R0
						5 => x"1133",			-- M[51] <- R1 		mov M[51], R1
						6 => x"1164",			-- M[100]<- R1		mov M[100], R1
						7 => x"4100",			-- R1 <- R1 + R0	add R1, R0
						8 => x"0064",			-- R0 <- M[100]		mov R0, M[100]
						9 => x"2210",			-- M[R2] <- R1 		mov M[R2], R1
						10 => x"4230",			-- R2 <- R2 + R3 	add R2, R3
						11 => x"043B",			-- R4 <- M[59]		mov R4, M[59]
						12 => x"6406",  		-- R4=0: PC<- #6	jz R4, #6
				
						13 => x"7032",			-- output<- M[50]   mov obuf_out,M[50]
						14 => x"7033",			-- output<- M[51]   mov obuf_out,M[51]
						15 => x"7034",			-- output<- M[52]   mov obuf_out,M[52]
						16 => x"7035",			-- output<- M[53]   mov obuf_out,M[53]
						17 => x"7036",			-- output<- M[54]   mov obuf_out,M[54]
						18 => x"7037",			-- output<- M[55]   mov obuf_out,M[55]
						19 => x"7038",			-- output<- M[56]   mov obuf_out,M[56]
						20 => x"7039",			-- output<- M[57]   mov obuf_out,M[57]
						21 => x"703A",			-- output<- M[58]   mov obuf_out,M[58]
						22 => x"703B",			-- output<- M[59]   mov obuf_out,M[59]			
						23 => x"F000",			-- halt
						others => x"0000");
		else
			if (clock'event and clock = '1') then
				if (Mwe ='1' and Mre = '0') then
					tmp_ram(conv_integer(address)) <= data_in;
				end if;
			end if;
		end if;
	end process;

    read: process(clock, rst, Mwe, address)
	begin
		if rst='1' then
			data_out <= ZERO;
		else
			if (clock'event and clock = '1') then
				if (Mre ='1' and Mwe ='0') then								 
					data_out <= tmp_ram(conv_integer(address));
				end if;
			end if;
		end if;
	end process;
end behv;