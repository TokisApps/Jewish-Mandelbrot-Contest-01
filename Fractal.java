import org.apache.commons.numbers.complex.*;
import javax.swing.*;
import java.awt.image.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import javax.imageio.*;


public class Fractal {
	Complex c = Complex.ZERO;
        Complex c2 = Complex.ZERO;
        Complex c3 = Complex.ZERO;
        Complex cv = Complex.ZERO;
        Complex c2v = Complex.ZERO;
        Complex c3v = Complex.ZERO;

	class MyThread extends Thread {
		boolean newData = false;
		double[] sums = null;
		double maxx;
		double minx;
		double my;

		public void run() {
			while(true) {
				while(!newData) try { sleep(1); } catch(Exception x) {}

				for(int j = 0;j < sums.length;++j) {
						double mx = j * (maxx - minx) / sums.length + minx;

						Complex z = Complex.ofCartesian(mx,my);
						ArrayList<Complex> zs = new ArrayList<>();

						double sum = 0;
                for(var k = 0;k < 30;++k) {
                    Complex z2 = f(z);
                    if(zs.size() >= 3) {
                        double sum2 = sum + Math.abs(
                            zs.get(zs.size() - 1).subtract(zs.get(zs.size() - 2)).arg() -
                            zs.get(zs.size() - 2).subtract(zs.get(zs.size() - 3)).arg()
                        );
                        if(Double.isFinite(sum2)) sum = sum2; else sum = 0;
                    }
                    if(z2.isFinite()) {z = z2;zs.add(z);}
                }

						sums[j] = sum;
					}



				newData = false;
			}
		}
	}

	class MyComponent extends JComponent {
			final int w = 300;
			final int h = 300;
			double[][] sums = new double[w][h];
			double[] rs = new double[] {
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random()
			};
			double summin;
			double summax;
			double mxmin = -13.1 * (Math.random() - 0.5);
			double mxmax = 13.1 * (Math.random() - 0.5);
			double mymin = -13.1 * (Math.random() - 0.5);
			double mymax = 13.1 * (Math.random() - 0.5);
			double mxminv = 0.1 * (Math.random() - 0.5);
			double mxmaxv = 0.1 * (Math.random() - 0.5);
			double myminv = 0.1 * (Math.random() - 0.5);
			double mymaxv = 0.1 * (Math.random() - 0.5);

			BufferedImage img = new BufferedImage(w,h,BufferedImage.TYPE_INT_RGB);
			MyThread[] ts = new MyThread[] {
				new MyThread(),
				    new MyThread(),
				    new MyThread()
			};

			public void init() {
						for(MyThread t : ts) t.start();
			}

			public void compute() {
				for(int i = 0;i < w;++i) l:{
					double mx = i * (mxmax - mxmin) / w + mxmin;

					boolean find = true;
					while(find) {
						for(MyThread t : ts) {
							if(!t.newData) {
								t.sums = sums[i];
								t.maxx = mymax;
								t.minx = mymin;
								t.my = mx;
								t.newData = true;
								find = false;
							}
						}

						try { Thread.sleep(1); } catch(Exception x) {}
					}
				}

				boolean found = false;
				do {
					found = false;
					for(MyThread t : ts) found |= t.newData;
				} while(found);

				summin = 1000000;
				summax = -1000000;

				for(int i = 0;i < w;++i)
					for(int j = 0;j < h;++j)
						if(sums[i][j] < summin)
							summin = sums[i][j];
						else if(sums[i][j] > summax)
							summax = sums[i][j];



        cv = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.01).add(cv);
        c2v = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.01).add(c2v);
        c3v = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.01).add(c3v);
        c = c.add(cv.multiply(0.01));
        c2 = c2.add(c2v.multiply(0.01));
        c3 = c3.add(c3v.multiply(0.01));

	mxminv += 0.1 * (Math.random() - 0.5);
	mxmaxv += 0.1 * (Math.random() - 0.5);
	myminv += 0.1 * (Math.random() - 0.5);
	mymaxv += 0.1 * (Math.random() - 0.5);

	mxmin += 0.1 * mxminv;
	mxmax += 0.1 * mxmaxv;
	mymin += 0.1 * myminv;
	mymax += 0.1 * mymaxv;

		 rs = new double[] {
				Math.random() + 0.5,
				Math.random(),
				Math.random() + 0.5,
				Math.random(),
				Math.random() + 0.5,
				Math.random()
			};
				for(int x = 0;x < w;++x) {
					for(int y = 0;y < h;++y) {
						double t = (sums[x][y] - summin) / (summax - summin);
						img.setRGB(x,y,
							new Color(
								(int)Math.round(120 * (Math.sin(rs[0] * 12 * t + 3 * rs[1]) + 1)),
								(int)Math.round(120 * (Math.sin(rs[2] * 12 * t + 3 * rs[3]) + 1)),
								(int)Math.round(120 * (Math.sin(rs[4] * 12 * t + 3 * rs[5]) + 1))
							).getRGB()
						);
					}
				}

			repaint();

			}

			public void paintComponent(Graphics g) {
				g.drawImage(img,0,0,getWidth(),getHeight(),null);
				

			}
		}




	Complex f(Complex z) {
		return (z.pow(c3).subtract(Complex.ONE)).add(z.add(c2).exp()).add(c);
	}


	public static void main(String[] args) {
		new Fractal();
	}

	public Fractal() {
		System.out.println(Complex.ofCartesian(0,0));

		JFrame f = new JFrame();
		final MyComponent comp = new MyComponent();
		comp.init();
		f.getContentPane().setLayout(new BorderLayout());
		f.getContentPane().add(comp,BorderLayout.CENTER);

		JButton b = new JButton("Save");
		f.getContentPane().add(b,BorderLayout.SOUTH);

		b.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String fn = "";
				ArrayList<Character> xs = new ArrayList<>();
				Random rnd = new Random();

				for(int i = 0;i < 26;++i) {
					xs.add((char)('a' + i));
					xs.add((char)('Z' + i));
				}

				for(int i = 0;i < 10;++i) {
					xs.add((char)('0' + i));
				}

				for(int i = 0;i < 10;++i) {
					fn += xs.get(rnd.nextInt(xs.size()));
				}

				fn += ".jpg";

				File f = new File(fn);

				try {
					ImageIO.write(comp.img, "JPG", f);
				} catch(Exception ex) {
					ex.printStackTrace();
				}
			}
		});

		final java.util.Timer t = new java.util.Timer();
		t.scheduleAtFixedRate(new TimerTask() {
			public void run() {
				comp.compute();

				File f = new File("background.jpg");

				try {
					ImageIO.write(comp.img, "JPG", f);
				} catch(Exception ex) {
					ex.printStackTrace();
				}
			}
		},0,5000);

		f.setSize(800,600);
		//f.setVisible(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		try {
			Thread.sleep(100);
		} catch(Exception ex) {
		}
	}
}



