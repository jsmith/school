--------------------------------------------------------
-- Simple Microprocessor Design (ESD Book Chapter 3)
-- Copyright 2001 Weijun Zhang
--
-- big multiplexor of control unit has
-- four 16-bit inputs and one 16-bit output
-- bigmux.vhd
--------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity bigmux is
port( 	Ia: 	in std_logic_vector(15 downto 0);
		Ib: 	in std_logic_vector(15 downto 0);	  
		Ic:	in std_logic_vector(15 downto 0);
		Id:	in std_logic_vector(15 downto 0);
		Option:	in std_logic_vector(1 downto 0);
		Muxout:	out std_logic_vector(15 downto 0)
);
end bigmux;

architecture behv of bigmux is

begin
    
    process(Ia, Ib, Ic, Id, Option)
    begin
      case Option is
	when "00" => Muxout <= Ia;
    when "01" => Muxout <= Ib;
	when "10" => Muxout <= Ic; 
	when "11" => Muxout <= Id;
	when others =>  
      end case;
    end process;

end behv;
