import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.Dimension;
import java.awt.Font;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.SwingConstants;

public class Gui extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -2409399182808273539L;
	private JPanel jContentPane = null;
	private JPanel Tools_Panel = null;
	/**
	 * This is the default constructor
	 */
	String path = null;
	static final int LINETOOL = 0;
	static final int RECTTOOL = 1;
	static final int POLYTOOL = 2;
	static Color cor;
	private JButton color_Button = null;
	private JTextField jTextField = null;
	private JLabel jLabel = null;
	private JLabel jLabel1 = null;
	private JLabel jLabel2 = null;
	private JTextField jTextField1 = null;
	private JLabel jLabel3 = null;
	private JLabel jLabel4 = null;
	private JTextField jTextField2 = null;
	private JTextField jTextField3 = null;
	private JPanel jPanel = null;
	private JLabel jLabel5 = null;
	private JLabel jLabel6 = null;
	private JTextField jTextField4 = null;
	private JPanel jPanel1 = null;
	private JPanel jPanel2 = null;
	private JLabel jLabel7 = null;
	private JLabel jLabel8 = null;
	private JTextField jTextField5 = null;
	private JLabel jLabel9 = null;
	private JLabel jLabel10 = null;
	private JTextField jTextField6 = null;
	private JTextField jTextField7 = null;
	private JLabel jLabel11 = null;
	public Gui()
	{
         initialize();
         pack();
    }

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(550, 400);
		this.setPreferredSize(new Dimension(550, 400));
		this.setContentPane(getJContentPane());
		this.setTitle("Reconhecimento de Assinaturas");
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jContentPane = new JPanel();
			jContentPane.setLayout(new BorderLayout());
			jContentPane.add(getTools_Panel(), BorderLayout.NORTH);
			jContentPane.add(getJPanel(), BorderLayout.SOUTH);
			jContentPane.add(getJPanel1(), BorderLayout.EAST);
			jContentPane.add(getJPanel2(), BorderLayout.WEST);
		}
		return jContentPane;
	}

	/**
	 * This method initializes Tools_Panel	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getTools_Panel() {
		if (Tools_Panel == null) {
			GridBagConstraints gridBagConstraints14 = new GridBagConstraints();
			gridBagConstraints14.gridx = 1;
			gridBagConstraints14.gridy = 5;
			jLabel11 = new JLabel();
			jLabel11.setText("Threshold:");
			jLabel11.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel11.setPreferredSize(new Dimension(265, 20));
			GridBagConstraints gridBagConstraints3 = new GridBagConstraints();
			gridBagConstraints3.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints3.gridy = 5;
			gridBagConstraints3.weightx = 1.0;
			gridBagConstraints3.gridx = 2;
			GridBagConstraints gridBagConstraints9 = new GridBagConstraints();
			gridBagConstraints9.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints9.gridy = 4;
			gridBagConstraints9.weightx = 1.0;
			gridBagConstraints9.gridx = 2;
			GridBagConstraints gridBagConstraints8 = new GridBagConstraints();
			gridBagConstraints8.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints8.gridy = 3;
			gridBagConstraints8.weightx = 1.0;
			gridBagConstraints8.gridx = 2;
			GridBagConstraints gridBagConstraints7 = new GridBagConstraints();
			gridBagConstraints7.gridx = 1;
			gridBagConstraints7.gridy = 4;
			jLabel4 = new JLabel();
			jLabel4.setText("Momentum:");
			jLabel4.setPreferredSize(new Dimension(265, 20));
			jLabel4.setFont(new Font("Dialog", Font.PLAIN, 12));
			GridBagConstraints gridBagConstraints6 = new GridBagConstraints();
			gridBagConstraints6.gridx = 1;
			gridBagConstraints6.gridy = 3;
			jLabel3 = new JLabel();
			jLabel3.setText("Learning Rate:");
			jLabel3.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel3.setPreferredSize(new Dimension(265, 20));
			GridBagConstraints gridBagConstraints5 = new GridBagConstraints();
			gridBagConstraints5.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints5.gridy = 2;
			gridBagConstraints5.weightx = 1.0;
			gridBagConstraints5.gridx = 2;
			GridBagConstraints gridBagConstraints41 = new GridBagConstraints();
			gridBagConstraints41.gridx = 1;
			gridBagConstraints41.gridy = 2;
			jLabel2 = new JLabel();
			jLabel2.setText("Nr. de neurónios para a camada intermédia:");
			jLabel2.setPreferredSize(new Dimension(265, 20));
			jLabel2.setFont(new Font("Dialog", Font.PLAIN, 12));
			GridBagConstraints gridBagConstraints31 = new GridBagConstraints();
			gridBagConstraints31.gridx = 1;
			gridBagConstraints31.gridy = 0;
			jLabel1 = new JLabel();
			jLabel1.setText("Criar Nova Rede");
			GridBagConstraints gridBagConstraints22 = new GridBagConstraints();
			gridBagConstraints22.gridx = 1;
			gridBagConstraints22.gridy = 1;
			jLabel = new JLabel();
			jLabel.setText("Directório com as assinaturas para treino: ");
			jLabel.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel.setPreferredSize(new Dimension(265, 20));
			GridBagConstraints gridBagConstraints12 = new GridBagConstraints();
			gridBagConstraints12.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints12.gridy = 1;
			gridBagConstraints12.weightx = 1.0;
			gridBagConstraints12.gridx = 2;
			Tools_Panel = new JPanel();
			Tools_Panel.setLayout(new GridBagLayout());
			Tools_Panel.setPreferredSize(new Dimension(120, 150));
			Tools_Panel.add(getJTextField2(), gridBagConstraints12);
			Tools_Panel.add(jLabel, gridBagConstraints22);
			Tools_Panel.add(jLabel1, gridBagConstraints31);
			Tools_Panel.add(jLabel2, gridBagConstraints41);
			Tools_Panel.add(getJTextField1(), gridBagConstraints5);
			Tools_Panel.add(jLabel3, gridBagConstraints6);
			Tools_Panel.add(jLabel4, gridBagConstraints7);
			Tools_Panel.add(getJTextField22(), gridBagConstraints8);
			Tools_Panel.add(getJTextField3(), gridBagConstraints9);
			Tools_Panel.add(getJTextField7(), gridBagConstraints3);
			Tools_Panel.add(jLabel11, gridBagConstraints14);
		}
		return Tools_Panel;
	}

	public void clear()
	{
        pack();
	}



	/**
	 * This method initializes color_Button	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getColor_Button() {
		if (color_Button == null) {
			color_Button = new JButton();
			color_Button.setText("Reconhecer");
			color_Button.setPreferredSize(new Dimension(115, 25));
			color_Button.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
			color_Button.addMouseListener(new java.awt.event.MouseListener() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					//System.out.println("mouseClicked()"); // TODO Auto-generated Event stub mouseClicked()
					//cor = JColorChooser.showDialog(new JFrame(), " ", cor);
					String dir_treino = jTextField.getText();
					String nr_neuronios = jTextField1.getText();
					String learning_rate = jTextField2.getText();
					String momentum = jTextField3.getText();
					String threshold = jTextField7.getText();
					
					String salvar = jTextField6.getText();
					String carregar = jTextField5.getText();
					
					String rec = jTextField4.getText();
					
					String cmd = new String();
					
					cmd = "/home/rei/Projects/iart-f1/iart-f1.exe";
					
					if (nr_neuronios.length() > 0) {
						cmd = cmd + " -n " + nr_neuronios;
					}
					if (learning_rate.length() > 0) {
						cmd = cmd + " -b " + learning_rate;
					}
					if (momentum.length() > 0) {
						cmd = cmd + " -a " + momentum;
					}
					if (threshold.length() > 0) {
						cmd = cmd + " -e " + threshold;
					}
					if (dir_treino.length() > 0) {
						cmd = cmd + " -t " + dir_treino;
					}
					if (salvar.length() > 0) {
						cmd = cmd + " -s " + salvar;
					}
					if (carregar.length() > 0) {
						cmd = cmd + " -l " + carregar;
					}
					if (rec.length() > 0) {
						cmd = cmd + " " + rec;
					}
					Process p = null;
					String s = null;
					String res = new String();
					try {
						p = Runtime.getRuntime().exec(cmd);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					
					BufferedReader stdInput = new BufferedReader(new 
			                 InputStreamReader(p.getInputStream()));
					
					try {
						while ((s = stdInput.readLine()) != null) {
						    res = res + "\n" + s;
						    System.out.println(s);
						}
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					
					JFrame nframe = new JFrame("Resultado");
					//Add contents to the window.
					nframe.add(new TextDisplay(res));
			        nframe.setLocation(400, 350);
			        //Display the window.
			        nframe.pack();
			        nframe.setVisible(true);
			        
				}
				public void mousePressed(java.awt.event.MouseEvent e) {
				}
				public void mouseReleased(java.awt.event.MouseEvent e) {
				}
				public void mouseEntered(java.awt.event.MouseEvent e) {
				}
				public void mouseExited(java.awt.event.MouseEvent e) {
				}
			});
		}
		return color_Button;
	}

	/**
	 * This method initializes jTextField	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField2() {
		if (jTextField == null) {
			jTextField = new JTextField();
			jTextField.setPreferredSize(new Dimension(250, 20));
			jTextField.setHorizontalAlignment(JTextField.LEFT);
		}
		return jTextField;
	}

	/**
	 * This method initializes jTextField1	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField1() {
		if (jTextField1 == null) {
			jTextField1 = new JTextField();
			jTextField1.setPreferredSize(new Dimension(250, 20));
		}
		return jTextField1;
	}

	/**
	 * This method initializes jTextField2	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField22() {
		if (jTextField2 == null) {
			jTextField2 = new JTextField();
			jTextField2.setPreferredSize(new Dimension(250, 20));
		}
		return jTextField2;
	}

	/**
	 * This method initializes jTextField3	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField3() {
		if (jTextField3 == null) {
			jTextField3 = new JTextField();
			jTextField3.setPreferredSize(new Dimension(250, 20));
		}
		return jTextField3;
	}

	/**
	 * This method initializes jPanel	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel() {
		if (jPanel == null) {
			GridBagConstraints gridBagConstraints4 = new GridBagConstraints();
			gridBagConstraints4.gridx = 1;
			gridBagConstraints4.gridy = 3;
			GridBagConstraints gridBagConstraints2 = new GridBagConstraints();
			gridBagConstraints2.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints2.gridy = 1;
			gridBagConstraints2.weightx = 1.0;
			gridBagConstraints2.gridx = 1;
			GridBagConstraints gridBagConstraints1 = new GridBagConstraints();
			gridBagConstraints1.gridx = 0;
			gridBagConstraints1.gridy = 1;
			jLabel6 = new JLabel();
			jLabel6.setText("Directório ou ficheiro de assinatura(s):");
			jLabel6.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel6.setPreferredSize(new Dimension(265, 20));
			GridBagConstraints gridBagConstraints = new GridBagConstraints();
			gridBagConstraints.gridx = 0;
			gridBagConstraints.gridy = 0;
			jLabel5 = new JLabel();
			jLabel5.setText("Reconhecer Assinatura");
			jLabel5.setHorizontalAlignment(SwingConstants.CENTER);
			jLabel5.setPreferredSize(new Dimension(200, 20));
			jPanel = new JPanel();
			jPanel.setLayout(new GridBagLayout());
			jPanel.setPreferredSize(new Dimension(120, 150));
			jPanel.add(jLabel5, gridBagConstraints);
			jPanel.add(jLabel6, gridBagConstraints1);
			jPanel.add(getJTextField4(), gridBagConstraints2);
			jPanel.add(getColor_Button(), gridBagConstraints4);
		}
		return jPanel;
	}

	/**
	 * This method initializes jTextField4	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField4() {
		if (jTextField4 == null) {
			jTextField4 = new JTextField();
			jTextField4.setPreferredSize(new Dimension(200, 20));
		}
		return jTextField4;
	}

	/**
	 * This method initializes jPanel1	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel1() {
		if (jPanel1 == null) {
			GridBagConstraints gridBagConstraints13 = new GridBagConstraints();
			gridBagConstraints13.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints13.gridy = 1;
			gridBagConstraints13.weightx = 1.0;
			gridBagConstraints13.gridx = 1;
			GridBagConstraints gridBagConstraints11 = new GridBagConstraints();
			gridBagConstraints11.gridx = 0;
			gridBagConstraints11.gridy = 1;
			jLabel8 = new JLabel();
			jLabel8.setText("Nome do ficheiro:");
			jLabel8.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel8.setPreferredSize(new Dimension(125, 20));
			GridBagConstraints gridBagConstraints10 = new GridBagConstraints();
			gridBagConstraints10.gridx = 0;
			gridBagConstraints10.anchor = GridBagConstraints.WEST;
			gridBagConstraints10.gridy = 0;
			jLabel7 = new JLabel();
			jLabel7.setText("Carregar Rede");
			jLabel7.setPreferredSize(new Dimension(87, 20));
			jPanel1 = new JPanel();
			jPanel1.setLayout(new GridBagLayout());
			jPanel1.setPreferredSize(new Dimension(250, 100));
			jPanel1.add(jLabel7, gridBagConstraints10);
			jPanel1.add(jLabel8, gridBagConstraints11);
			jPanel1.add(getJTextField5(), gridBagConstraints13);
		}
		return jPanel1;
	}

	/**
	 * This method initializes jPanel2	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel2() {
		if (jPanel2 == null) {
			GridBagConstraints gridBagConstraints17 = new GridBagConstraints();
			gridBagConstraints17.fill = GridBagConstraints.VERTICAL;
			gridBagConstraints17.gridy = 1;
			gridBagConstraints17.weightx = 1.0;
			gridBagConstraints17.gridx = 1;
			GridBagConstraints gridBagConstraints16 = new GridBagConstraints();
			gridBagConstraints16.gridx = 0;
			gridBagConstraints16.gridy = 1;
			jLabel10 = new JLabel();
			jLabel10.setText("Nome do ficheiro:");
			jLabel10.setFont(new Font("Dialog", Font.PLAIN, 12));
			jLabel10.setPreferredSize(new Dimension(125, 20));
			GridBagConstraints gridBagConstraints15 = new GridBagConstraints();
			gridBagConstraints15.gridx = 0;
			gridBagConstraints15.anchor = GridBagConstraints.WEST;
			gridBagConstraints15.gridy = 0;
			jLabel9 = new JLabel();
			jLabel9.setText("Salvar Rede");
			jLabel9.setPreferredSize(new Dimension(71, 20));
			jPanel2 = new JPanel();
			jPanel2.setLayout(new GridBagLayout());
			jPanel2.setPreferredSize(new Dimension(250, 100));
			jPanel2.add(jLabel9, gridBagConstraints15);
			jPanel2.add(jLabel10, gridBagConstraints16);
			jPanel2.add(getJTextField6(), gridBagConstraints17);
		}
		return jPanel2;
	}

	/**
	 * This method initializes jTextField5	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField5() {
		if (jTextField5 == null) {
			jTextField5 = new JTextField();
			jTextField5.setPreferredSize(new Dimension(125, 20));
		}
		return jTextField5;
	}

	/**
	 * This method initializes jTextField6	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField6() {
		if (jTextField6 == null) {
			jTextField6 = new JTextField();
			jTextField6.setPreferredSize(new Dimension(125, 20));
			jTextField6.setHorizontalAlignment(JTextField.LEADING);
		}
		return jTextField6;
	}

	/**
	 * This method initializes jTextField7	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField7() {
		if (jTextField7 == null) {
			jTextField7 = new JTextField();
			jTextField7.setPreferredSize(new Dimension(250, 20));
		}
		return jTextField7;
	}

}  //  @jve:decl-index=0:visual-constraint="6,-4"
