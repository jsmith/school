------------------------------------------------------------------------
-- Simple Microprocessor Design (ESD Book Chapter 3)
-- Copyright Spring 2001 Weijun Zhang
--
-- Control Unit composed of Controller, PC, IR and multiplexor
-- VHDL structural modeling
-- ctrl_unit.vhd
------------------------------------------------------------------------

library	ieee;
use ieee.std_logic_1164.all;  
use ieee.std_logic_arith.all;			   
use ieee.std_logic_unsigned.all;
use work.MP_lib.all;

entity ctrl_unit is
port(	clock_cu:	in 	std_logic;
	rst_cu:		in 	std_logic;
	PCld_cu:	in 	std_logic;
	mdata_out: 	in 	std_logic_vector(15 downto 0);
	dpdata_out:	in 	std_logic_vector(15 downto 0);
	maddr_in:	out std_logic_vector(15 downto 0);		  
	immdata:	out std_logic_vector(15 downto 0);
	RFs_cu:		out	std_logic_vector(1 downto 0);
	RFwa_cu:	out	std_logic_vector(3 downto 0);
	RFr1a_cu:	out	std_logic_vector(3 downto 0);
	RFr2a_cu:	out	std_logic_vector(3 downto 0);
	RFwe_cu:	out	std_logic;
	RFr1e_cu:	out	std_logic;
	RFr2e_cu:	out	std_logic;
	jpen_cu:	out std_logic;
	ALUs_cu:	out	std_logic_vector(2 downto 0);	
	Mre_cu:		out std_logic;
	Mwe_cu:		out std_logic;
	oe_cu:		out std_logic
);
end ctrl_unit;

architecture struct of ctrl_unit is

signal IR_sig: std_logic_vector(15 downto 0);
signal PCinc_sig, PCclr_sig, IRld_sig: std_logic;
signal Ms_sig: std_logic_vector(1 downto 0);
signal PC2mux: std_logic_vector(15 downto 0);
signal IR2mux_a, IR2mux_b: std_logic_vector(15 downto 0);

begin

  IR2mux_b <= "000000000000" & IR_sig(11 downto 8);	
  immdata <= "00000000" & IR_sig(7 downto 0);
  
  U0: controller port map(clock_cu,rst_cu,IR_sig,RFs_cu,RFwa_cu,
			    RFr1a_cu,RFr2a_cu,RFwe_cu,RFr1e_cu,
			    RFr2e_cu,ALUs_cu,jpen_cu,PCinc_sig,
			    PCclr_sig,IRld_sig,Ms_sig,Mre_cu,Mwe_cu,oe_cu);
  U1: PC port map(clock_cu,PCld_cu, PCinc_sig, PCclr_sig, IR2mux_a, PC2mux);
  U2: IR port map(mdata_out, IRld_sig, IR2mux_a, IR_sig);
  U3: bigmux port map(dpdata_out,IR2mux_a,PC2mux,IR2mux_b,Ms_sig,maddr_in);

end struct;