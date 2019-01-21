--------------------------------------------------------
-- Simple Microprocessor Design (ESD Book Chapter 3)
-- Copyright 2001, Weijun Zhang
--
-- Instruction Register
-- IR.vhd
--------------------------------------------------------

library	ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity IR is
port(	IRin:	  in std_logic_vector(15 downto 0);
		IRld:	  in std_logic;
		dir_addr: out std_logic_vector(15 downto 0);
		IRout: 	  out std_logic_vector(15 downto 0)
);
end IR;

architecture behv of IR is

begin
  process(IRld, IRin)
  begin
    if IRld = '1' then
	  IRout <= IRin;
	  dir_addr <= "00000000" & IRin(7 downto 0);
    end if;
  end process;
end behv;










