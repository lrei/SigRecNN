//package rei.feup.cpal;
/* TextDemo.java requires no other files. */

import java.awt.*;
import javax.swing.*;

public class TextDisplay extends JPanel  {
	private static final long serialVersionUID = 6615436133849532811L;
	protected JTextArea textArea;

    public TextDisplay(String cp) {
        super(new GridBagLayout());

        textArea = new JTextArea(20, 50);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea,
                                       JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                                       JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        //Add Components to this panel.
        GridBagConstraints c = new GridBagConstraints();
        c.gridwidth = GridBagConstraints.REMAINDER;

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1.0;
        c.weighty = 1.0;
        add(scrollPane, c);

        textArea.append(cp);
    }



}
