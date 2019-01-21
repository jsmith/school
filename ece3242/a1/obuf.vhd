----------------------------------------------------------
-- Simple Microprocessor Design (ESD Book Chapter 3)
-- Copyright 2001 Weijun Zhang
--
-- Output buffer of Data Path
-- obuf.vhd
----------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use work.MP_lib.all;

entity obuf is
port(	O_en: 		in std_logic;
	obuf_in: 	in std_logic_vector(15 downto 0);
	obuf_out: 	out std_logic_vector(15 downto 0)
);
end obuf;

architecture behv of obuf is
begin

  process (O_en, obuf_in)
  begin
    if O_en = '1' then
	obuf_out <= obuf_in;
    else
	obuf_out <= HIRES;
    end if;
  end process;

end behv;






