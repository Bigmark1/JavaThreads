package concurrent;


public class ProcessCounter implements Runnable {
	
	

	public static void main(String[] args) throws InterruptedException {
		
		Runnable countUp = new ProcessCounter(); 
		Runnable countDwn = new Counting(); 
		
		Thread t1 = new Thread(countUp); 
		Thread t2 = new Thread(countDwn); 
	
		t1.start();
		t1.join();
		t2.start(); 	
		t2.join(); 
		
	
		}
	

	@Override
	public void run() {
		int count =0; 
		while(count <= 20) {
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				
				e.printStackTrace();
			}
			System.out.print(count++ + " ");
			 
		}
		System.out.println(" "); 
	}
	
	

	

}

 class Counting implements Runnable {
  
	@Override
	public void run() {
		int count =20; 
		while(count >= 0) {
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.print(count-- + " ");
			 
		}
		
		
	}
	
}
