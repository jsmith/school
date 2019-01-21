library verilog;
use verilog.vl_types.all;
entity SimpleCompArch is
    port(
        sys_clk         : in     vl_logic;
        sys_rst         : in     vl_logic;
        sys_output      : out    vl_logic_vector(15 downto 0);
        D_rfout_bus     : out    vl_logic_vector(15 downto 0);
        D_RFwa          : out    vl_logic_vector(3 downto 0);
        D_RFr1a         : out    vl_logic_vector(3 downto 0);
        D_RFr2a         : out    vl_logic_vector(3 downto 0);
        D_RFwe          : out    vl_logic;
        D_RFr1e         : out    vl_logic;
        D_RFr2e         : out    vl_logic;
        D_RFs           : out    vl_logic_vector(1 downto 0);
        D_ALUs          : out    vl_logic_vector(2 downto 0);
        D_PCld          : out    vl_logic;
        D_jpz           : out    vl_logic;
        D_mdout_bus     : out    vl_logic_vector(15 downto 0);
        D_mdin_bus      : out    vl_logic_vector(15 downto 0);
        D_mem_addr      : out    vl_logic_vector(7 downto 0);
        D_Mre           : out    vl_logic;
        D_Mwe           : out    vl_logic
    );
end SimpleCompArch;
