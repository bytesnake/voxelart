import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;
import java.text.NumberFormat;

import java.awt.Font;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.*;
import javax.imageio.ImageIO;

public class FontGenerator
{
	public static void main(String[] args){
		if(args.length==4){
			int size=0;
			try{
				size=Integer.parseInt(args[2]);
			}catch(NumberFormatException e){
				System.err.println("fontsize must be an int");
				System.exit(1);
			}
			int textstyle=Font.PLAIN;
			if(args[3].equals("plain")){
				textstyle=Font.PLAIN;
			}else if(args[3].equals("bold")){
				textstyle=Font.BOLD;
			}else if(args[3].equals("italic")){
				textstyle=Font.ITALIC;
			}else if(args[3].equals("bolditalic")){
				textstyle=Font.BOLD|Font.ITALIC;
			}else{
				System.err.println("style must be plain | bold | italic | bolditalic");
				System.exit(1);
			}
			//Schriftart generieren
			generateFont(args[0],args[1],size,textstyle);
		}else if(args.length==5){
			int size=0;
			try{
				size=Integer.parseInt(args[3]);
			}catch(NumberFormatException e){
				System.err.println("fontsize must be an int");
				System.exit(1);
			}
			int textstyle=Font.PLAIN;
			if(args[4].equals("plain")){
				textstyle=Font.PLAIN;
			}else if(args[4].equals("bold")){
				textstyle=Font.BOLD;
			}else if(args[4].equals("italic")){
				textstyle=Font.ITALIC;
			}else if(args[4].equals("bolditalic")){
				textstyle=Font.BOLD|Font.ITALIC;
			}else{
				System.err.println("style must be plain | bold | italic | bolditalic");
				System.exit(1);
			}
			//Schriftart generieren
			generateFont(args[0],args[1],args[2],size,textstyle);
		}else{
			System.out.println("usage: java FontGenerator name fontname fontsize style");
			System.out.println(" or    java FontGenerator name font name fontsize style");
			System.exit(0);
		}
	}
	/**
	 * generiert die .png und .bfd-Dateien
	 */
	public static void generateFont(String filename,String font,int size,int style){
		try{
			BufferedImage fontImage = new BufferedImage(512,512, BufferedImage.TYPE_4BYTE_ABGR); //TODO andere Größen als 512x512 unterstützen
			Graphics2D g = (Graphics2D)fontImage.getGraphics();
			g.setFont(new Font(font,style,size));
			
			FontMetrics fm = g.getFontMetrics();
			BufferedOutputStream os= new BufferedOutputStream(new FileOutputStream(filename+".bfd"));
			os.write(fm.getHeight());

			for(int i=0;i<256;i++) {
				os.write(fm.charWidth(i)+1);
				int x = i % 16;
				int y = i / 16;
				char ch[] = {(char)i};
				String temp = new String(ch);
				g.drawString(temp, (x * 32) + 1, (y * 32) + fm.getAscent());
			}

			File file = new File(filename+".png");

			ImageIO.write(fontImage, "png", file);
			os.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

