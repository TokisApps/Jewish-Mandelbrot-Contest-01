import org.apache.commons.numbers.complex.*;
import javax.swing.*;
import java.awt.image.*;
import java.awt.*;
import java.util.*;


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
			final int w = 200;
			final int h = 200;
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
			double mxmin = -10;
			double mxmax = 10;
			double mymin = -10;
			double mymax = 10;

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



        cv = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.1).add(cv);
        c2v = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.01).add(c2v);
        c3v = Complex.ofCartesian((Math.random() - 0.5),(Math.random() - 0.5)).multiply(0.01).add(c3v);
        c = c.add(cv.multiply(0.001));
        c2 = c2.add(c2v.multiply(0.001));
        c3 = c3.add(c3v.multiply(0.001));

		 rs = new double[] {
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random(),
				Math.random()
			};

			repaint();

			}

			public void paintComponent(Graphics g) {
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

		final java.util.Timer t = new java.util.Timer();
		t.scheduleAtFixedRate(new TimerTask() {
			public void run() {
				comp.compute();
			}
		},0,100);

		f.setSize(800,600);
		f.setVisible(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}
}



