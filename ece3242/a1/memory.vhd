--------------------------------------------------------
-- SSimple Computer Architecture
--
-- memory 256*16
-- 8 bit address; 16 bit data
-- memory.vhd
--------------------------------------------------------

library	ieee;
use ieee.std_logic_arith.all;
use ieee.std_logic_1164.all;
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
			tmp_ram <= (
                        -- Do initial setup.
                        0 => x"3001",	   		-- R0 <- #1                 Initial y(n - 2)
						1 => x"3103",			-- R1 <- #3                 Initial y(1)
						2 => x"3252",			-- R2 <- #82                Pointer to output location
                        3 => x"3301",			-- R3 <- #1                 Constant 1
                        4 => x"3501",			-- R5 <- #1                 Counter (n)
                        5 => x"3681",			-- R6 <- #1                 Constant -1
                        6 => x"3681",			-- R7 <- #1                 x (set to 1 for now)
						7 => x"1050",			-- M[80] <- R0              Set first value
						8 => x"1151",			-- M[81] <- R1              Set the second value

                        -- Start the actual program
                        9 => x"1164",			-- M[100]<- R1              Temporarily store R1
                        10 => x"4530",			-- R5 <- R5 + 1 (R3)        Increment n
                        11 => x"8160",			-- R1 <- R1 * -1            Get -y(n-1)
                        12 => x"4100",			-- R1 <- R1 + R0            Add y(n-2) to -y(n-1)
                        13 => x"3402",			-- R4 <- 2                  Set R4 to 2
                        14 => x"8470",			-- R4 <- 2 (R4) * x (R7)    Multiply 2 by x
                        15 => x"8450",			-- R4 <- 2x (R4) * n (R5)   Multiply 2x by n
                        16 => x"4140",			-- R1 <- R1 + R4            Add 2xn to -y(n-1) + y(n-2)
						17 => x"0064",			-- R0 <- M[100]             Set y(n-1) to y(n-2)
						18 => x"2210",			-- M[R2] <- R1              Store value
						19 => x"4230",			-- R2 <- R2 + 1 (R3)        Increment pointer
						20 => x"0859",			-- R8 <- M[89]              Get value from mem location 89
						21 => x"6809",  		-- if R8 != 0: PC <- 9      Loop if end is not reached

                        -- Display the output
						22 => x"7050",			-- output <- M[80]
						23 => x"7051",			-- output <- M[81]
						24 => x"7052",			-- output <- M[82]
						25 => x"7053",			-- output <- M[83]
						26 => x"7054",			-- output <- M[84]
						27 => x"7055",			-- output <- M[85]
						28 => x"7056",			-- output <- M[86]
						29 => x"7057",			-- output <- M[87]
						30 => x"7058",			-- output <- M[88]
                        31 => x"7059",			-- output <- M[89]
                        
                        -- Stop execution.
						32 => x"F000",			-- halt
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