/*  Test GUI for proposal comparison .
	Needs to include code.extractor and comparison packages
	when those tools are actually implemented
*/
//package code.extractor;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.EmptyBorder;
import java.awt.BorderLayout;
import org.eclipse.swt.browser.Browser;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

public class CPRGui extends JFrame implements ActionListener {
	// GUI Components
    private JPanel main = new JPanel(new BorderLayout ());
    private JPanel center = new JPanel(new BorderLayout());
    private JPanel top = new JPanel(new BorderLayout ());
    private JPanel left = new JPanel(new BorderLayout ());
    private JPanel runOption = new JPanel(new GridLayout ());
    private JPanel sorting = new JPanel(new FlowLayout ());
    private JPanel buttons = new JPanel(new FlowLayout ());
    private JScrollPane tableScroll;
    private JScrollPane leftScroll;
    private JScrollPane displayScroll;
    private JTextField browseFile = new JTextField(60);
    private JFormattedTextField dMin = new JFormattedTextField(NumberFormat.getNumberInstance());
    private JFormattedTextField kMin = new JFormattedTextField(NumberFormat.getNumberInstance());
    private JButton browse = new JButton("Browse for Folder");
    private JButton update = new JButton("Update XML");
    private JButton run = new JButton("Run");
    private JButton sortAuthor = new JButton("Author");
    private JButton sortName = new JButton("Name");
    private JButton sortDomain = new JButton("Domain");
    private JButton sortKeyword = new JButton("Keyword");
    private JLabel dMinLabel = new JLabel("Domain Min: ", SwingConstants.LEFT);
    private JLabel kMinLabel = new JLabel("Keyword Min: ", SwingConstants.LEFT);
    private JList propList = new JList();
    private JTable compData;
    private JTable display;
    private JComboBox authorList = new JComboBox();
    private JComboBox minCombo = new JComboBox();
    private DefaultListModel propListModel = new DefaultListModel();
    private DefaultTableModel tableModel = new DefaultTableModel();
    private DefaultTableModel displayModel = new DefaultTableModel();
    private DefaultComboBoxModel authorModel = new DefaultComboBoxModel();
	private Browser browser;
	
	private JTextField debug = new JTextField(60);
	
	// Public GUI Components
	JMenuBar menubar = new JMenuBar();
	JMenu file = new JMenu("File");
	JMenu tools = new JMenu("Tools");
	JMenu help = new JMenu("Help");
	JMenuItem exit = new JMenuItem("Exit");
	JMenuItem adv = new JMenuItem("Matrix Comparison");
	JMenuItem about = new JMenuItem("About");
	JFileChooser fc = new JFileChooser();
	
	// Variables
	ArrayList<Proposal> allProposals = new ArrayList<Proposal>(); 
	ArrayList<Proposal> currAuthorProposals = new ArrayList<Proposal>();
	Proposal currProposal = null;
	ArrayList<Proposal> currCompareProposals = new ArrayList<Proposal>();
	ArrayList<String> authors = new ArrayList<String>();
	Random gen = new Random(19580427);
    
	// Initialize the GUI
	public CPRGui() {
		// Initialize Panels
		getContentPane().setLayout(new BorderLayout());
		propList = new JList(propListModel);
		authorList = new JComboBox(authorModel);
		propList.setBorder(BorderFactory.createLineBorder(Color.gray));
		browse.setVisible(true);
		left.setMinimumSize(new Dimension(300,left.getMinimumSize().height));
		left.setPreferredSize(new Dimension(300,left.getPreferredSize().height));
		fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		update.setEnabled(false);
		browseFile.setEnabled(false);
		authorList.setEnabled(false);
		sortAuthor.setEnabled(false);
		sortName.setEnabled(false);
		sortDomain.setEnabled(false);
		sortKeyword.setEnabled(false);
		run.setEnabled(false);
		adv.setEnabled(false);
		
		// Set Tooltips
		browse.setToolTipText("Browse for Proposal Folder");
		run.setToolTipText("Run Comparison");
		
		// Set Action Listeners
		run.addActionListener(this);
		browse.addActionListener(this);
		update.addActionListener(this);
		authorList.addActionListener(this);
		sortAuthor.addActionListener(this);
		sortName.addActionListener(this);
		sortDomain.addActionListener(this);
		sortKeyword.addActionListener(this);
		adv.addActionListener(this);
		
		// Initialize Rating Options
		dMin.setText("50");
		kMin.setText("50");
		GridLayout runOptionLayout = new GridLayout(0,2);
		runOption.setLayout(runOptionLayout);
		minCombo.addItem("AND");
		minCombo.addItem("OR");
		runOption.add(dMinLabel);
		runOption.add(dMin);
		runOption.add(kMinLabel);
		runOption.add(kMin);
		runOption.add(minCombo);
		runOption.add(run);
		
		// Create Menu
		file.add(exit);
		tools.add(adv);
		help.add(about);
		menubar.add(file);
		menubar.add(tools);
		menubar.add(help);
		setJMenuBar(menubar);
		
		//Create dataTable
		String[] columnNames = {"Author", "Proposal Name", "Domain Rating", "Keyword Rating"};
		Object[][] data = { { "","","","","" } };
		tableModel = new DefaultTableModel(data,columnNames);
		compData = new JTable(tableModel);
		tableModel.removeRow(0);
		tableScroll = new JScrollPane(compData);
		compData.setRowHeight(20);
		compData.setFillsViewportHeight(true);
		
		// Add Components to Panels
		getContentPane().add("Center", main);

		main.add(top, "North");
		main.add(center, "Center");
		main.add(left,"West");
		//main.add(debug,"South");
		
		center.add(tableScroll,"Center");
		center.add(sorting,"South");
		
		top.add(browseFile, "Center");
		top.add(buttons, "East");
		
		buttons.add(browse);
		buttons.add(update);

		leftScroll = new JScrollPane(propList);
		left.add(runOption,"South");
		left.add(authorList,"North");
		left.add(leftScroll,"Center");
		
		sorting.add(sortAuthor);
		sorting.add(sortName);
		sorting.add(sortDomain);
		sorting.add(sortKeyword);
		
		//Borders
		main.setBorder(new EmptyBorder(new Insets(10,10,10,10)));
		top.setBorder(new EmptyBorder(new Insets(10,10,10,10)));
		left.setBorder(new EmptyBorder(new Insets(10,10,10,10)));
	}
	
	// Handle GUI actions
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == browse) {
			parseFolder(true);
		}
		if(e.getSource() == update) {
			parseFolder(false);
		}
		if(e.getSource() == adv) {
			getMatrix();
		}
		if(e.getSource() == authorList) {
			listProposals();
		}
		if(e.getSource() == run) {
			runComparison();
		}
		if(e.getSource() == sortAuthor) {
			fillTableByAuthor();
		}
		if(e.getSource() == sortName) {
			fillTableByName();
		}
		if(e.getSource() == sortDomain) {
			fillTableByDomain();
		}
		if(e.getSource() == sortKeyword) {
			fillTableByKeyword();
		}
	}
	
	// Parse a Folder for proposals
	// openDir = true if prompted for directory
	//			 false otherwise
	public void parseFolder(boolean openDir) {
		// Clear All
		allProposals.clear();
		currAuthorProposals.clear();
		currProposal = null;
		currCompareProposals.clear();
		authors.clear();
		propListModel.removeAllElements();
		tableModel.setRowCount(0);
		authorModel.removeAllElements();
		
		authorList.setEnabled(false);
		sortAuthor.setEnabled(false);
		sortName.setEnabled(false);
		sortDomain.setEnabled(false);
		sortKeyword.setEnabled(false);
		run.setEnabled(false);
		adv.setEnabled(false);
		
		// Open Folder
		File dir = null;
		if (openDir) {
			// Get a directory
			int retval = fc.showOpenDialog(CPRGui.this);
			dir = fc.getSelectedFile();
			update.setEnabled(true);
		} else {
			dir = new File(browseFile.getText());
		}
        String s = dir.getAbsolutePath();
        browseFile.setText(s);
		
		// Filter Files
		FilenameFilter filter = new FilenameFilter() {
		    public boolean accept(File dir, String name) {
		        return (name.endsWith(".html") || name.endsWith(".htm"));
		    }
		};

		// Parse Files and create listings
		String[] files = dir.list(filter);
		if (files == null) {
		    // Either dir does not exist or is not a directory
		} else {
		    for (int i=0; i<files.length; i++) {
		        String filename = files[i];
		        String author = getRandomAuthor();
		        allProposals.add(new Proposal(author,filename));
		        if (!authors.contains(author)) {
		        	authors.add(author);
		        }
		    }
		}
		
		// Fill Authors
		Collections.sort(authors);
		for(int i = 0; i < authors.size(); i++) {
			authorModel.addElement(authors.get(i).toString());
		}
		
		run.setEnabled(true);
		authorList.setEnabled(true);
	}
	
	// Fill list of proposals for current author
	public void listProposals() {
		if (authorModel.getSize()>0) {
			String currAuthor = authorList.getSelectedItem().toString();
			propListModel.removeAllElements();
			currAuthorProposals.clear();
			for (int i = 0; i < allProposals.size(); i++) {
				if(allProposals.get(i).getAuthor().equals(currAuthor)) {
					currAuthorProposals.add(allProposals.get(i));
				}
			}
			
			// Sort
			Collections.sort( currAuthorProposals, new Comparator<Proposal>()
			        {
			        public int compare( Proposal a, Proposal b )
			           {
			        	String aName = a.getName();
			        	String bName = b.getName();
			        	return aName.compareTo(bName);
			           }
			        } );
			
			// Add to List
			for(int i = 0; i < currAuthorProposals.size(); i++) {
				propListModel.addElement(currAuthorProposals.get(i).getName());
			}
		}
	}
	
	// Run a comparison on the current proposal and min ratings
	public void runComparison() {
		double doMin, keMin;
		boolean add;
		currProposal = currAuthorProposals.get(propList.getSelectedIndex());
		doMin = Double.parseDouble(dMin.getText());
		keMin = Double.parseDouble(kMin.getText());
		currCompareProposals.clear();
		
		for(int i = 0; i < allProposals.size(); i++) {
			add = false;
			Proposal iter = allProposals.get(i);
			iter.setDomain(getRandomDomain());
			iter.setKeyword(getRandomKeyword());
			if (minCombo.getSelectedItem().toString().equals("AND")) {
				if (iter.getDomain() >= doMin && iter.getKeyword() >= keMin) {
					add = true;
				}
			} else {
				if (iter.getDomain() >= doMin || iter.getKeyword() >= keMin) {
					add = true;
				}
			}
			
			if (add && currProposal != iter) {
				currCompareProposals.add(iter);				
			}
		}
		
		fillTableByDomain();

		sortAuthor.setEnabled(true);
		sortName.setEnabled(true);
		sortDomain.setEnabled(true);
		sortKeyword.setEnabled(true);
		adv.setEnabled(true);
	}
	
	// Run matrix comparison
	public void getMatrix() {
		ArrayList<Proposal> propMatrix = currCompareProposals;
		propMatrix.add(0,currProposal);
		int rows = currCompareProposals.size()+1;
		int cols = rows;
		Object[][] matrix = new Object[rows][cols];
		for(int i = 0; i<propMatrix.size(); i++) {
			matrix[0][i+1] = propMatrix.get(i).getAuthor() + "/" + propMatrix.get(i).getName();
			matrix[i+1][0] = propMatrix.get(i).getAuthor() + "/" + propMatrix.get(i).getName();
			for(int j = 0; j<propMatrix.size(); j++) {
				String value;
				if(i!=j) {
					value = getRandomDomain() + "/" + getRandomKeyword();
				} else {
					value = "-";
				}
				matrix[j+1][i+1] = value;
				matrix[i+1][j+1] = value;
			}
		}

		//MatrixCompare advPopup = new MatrixCompare(matrix,rows,cols);
		//Create dataTable
		String[] columnNames = new String[cols];
		displayModel = new DefaultTableModel(matrix,columnNames);
		display = new JTable(displayModel);
		displayScroll = new JScrollPane(display);
		display.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		for(int i = 0; i<display.getColumnCount(); i++) {
			TableColumn column = display.getColumnModel().getColumn(i);
			column.setPreferredWidth(200);
		}
		display.setRowSelectionAllowed(false);
		display.setRowHeight(60);
		
		JFrame matrixSheet = new JFrame();
		//JPanel matrixPanel = new JPanel(new BorderLayout());
		//matrixPanel.add(displayScroll,"Center");
		matrixSheet.add(displayScroll);
		matrixSheet.setSize(new Dimension(500,500));
		matrixSheet.setLocationRelativeTo(this);
		matrixSheet.setVisible(true);
	}
	
	// Fill Proposal Table
	public void fillTable() {
		Object[][] data = new Object[currCompareProposals.size()][4];
		tableModel.setRowCount(0);
		
		for(int i = 0; i<currCompareProposals.size(); i++) {
			data[i][0] = currCompareProposals.get(i).getAuthor();
			data[i][1] = currCompareProposals.get(i).getName();
			data[i][2] = currCompareProposals.get(i).getDomain();
			data[i][3] = currCompareProposals.get(i).getKeyword();
			tableModel.addRow(data[i]);
		}
	}
	
	// Sort Proposals by Name and Fill it
	public void fillTableByName() {
		// Sort
		Collections.sort( currCompareProposals, new Comparator<Proposal>()
		        {
		        public int compare( Proposal a, Proposal b )
		           {
		        	return a.getName().compareTo(b.getName());
		           }
		        } );
		fillTable();
	}
	
	// Sort Proposals by Author and Fill it
	public void fillTableByAuthor() {
		// Sort
		Collections.sort( currCompareProposals, new Comparator<Proposal>()
		        {
		        public int compare( Proposal a, Proposal b )
		           {
		        	return a.getAuthor().compareTo(b.getAuthor());
		           }
		        } );
		fillTable();
	}

	// Sort Proposals by Domain and Fill it
	public void fillTableByDomain() {
		// Sort
		Collections.sort( currCompareProposals, new Comparator<Proposal>()
		        {
		        public int compare( Proposal a, Proposal b )
		           {
		        	return (a.getDomain()>b.getDomain() ? -1 : (a.getDomain()==b.getDomain() ? 0 : 1));
		           }
		        } );	
		fillTable();
	}
	
	// Sort Proposals by Keyword and Fill it
	public void fillTableByKeyword() {
		// Sort
		Collections.sort( currCompareProposals, new Comparator<Proposal>()
		        {
		        public int compare( Proposal a, Proposal b )
		           {
		        	return (a.getKeyword()>b.getKeyword() ? -1 : (a.getKeyword()==b.getKeyword() ? 0 : 1));
		           }
		        } );	
		fillTable();
	}

	// Match a proposal with a random author
	public String getRandomAuthor() {
		int r = gen.nextInt(6);
		String randomAuthor = null;
		if (r==0) {
			randomAuthor = "Rafael Zanatta";
		}
		if (r==1) {
			randomAuthor = "Yevgen Biletskiy";
		}
		if (r==2) {
			randomAuthor = "Bill Gates";
		}
		if (r==3) {
			randomAuthor = "Stephen Hawking";
		}
		if (r==4) {
			randomAuthor = "Michael Bay";
		}
		if (r==5) {
			randomAuthor = "William Briggs";
		}
		if (r==6) {
			randomAuthor = "Craig Whynot";
		}
		if (r==7) {
			randomAuthor = "Jonathan Walker";
		}
		
		return randomAuthor;
	}
	
	// Apply random Domain Rating
	public double getRandomDomain() {
		return gen.nextInt(100);
	}
	
	// Apply random Keyword Rating
	public double getRandomKeyword() {
		return gen.nextInt(100);
	}
	
	// Initialize extraction logic
	public void run(){
		//ExtractionLogic extr = new ExtractionLogic();
	}
	
	// Main
	public static void main(String[] args) {
		CPRGui gui = new CPRGui();
		try {
	       // UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
	    }
		catch (Exception evt) { }
	    UIManager.put ("ToolTip.background", Color.blue);
	    UIManager.put ("ToolTip.foreground", Color.white);
		gui.setTitle("Comparison Tool GUI");
		gui.setSize(1000, 600);
		gui.setLocationRelativeTo(null);                		//locate in middle of screen
		gui.setVisible(true);
		gui.addWindowListener(new WindowAdapter() {        	    //closes the GUI
			public void windowClosing(WindowEvent e){
			    System.exit(0);
			}
		});
	}
}

// Proposal class
class Proposal {

    private String author;				// prop author
    private String name;				// prop name
    private double tempDomainCompare;	// temp domain rate
    private double tempKeywordCompare;	// temp keyword rate

    // Constructor
    public Proposal(String author, String name) {
        this.author = author;
        this.name = name;
        this.tempDomainCompare = 0.0;
        this.tempKeywordCompare = 0.0;
    }

    public String getName() {
        return name;
    }

    public String getAuthor() {
    	return author;
    }

    public void setDomain(double in) {
    	tempDomainCompare = in;
    }

    public void setKeyword(double in) {
    	tempKeywordCompare = in;
    }

    public double getDomain() {
    	return tempDomainCompare;
    }

    public double getKeyword() {
    	return tempKeywordCompare;
    }
}
