public class Main {
    static final int N = 10;
    static Producer p = new Producer();
    static Consumer c = new Consumer();
    static Monitor mon = new Monitor();

    static public void main(String[] args) {
        p.start();
        c.start();
    }

    static class Producer extends Thread {
        public void run() {
            int item;
            while (true) {
                item = 2;
                mon.insert(item);
                System.out.println(mon.len);
                try {
                    sleep(500);
                } catch(InterruptedException e) {
                    System.out.println("Interrupt error.");
                }
            }
        }
    }

    static class Consumer extends Thread {
        public void run() {
            while(true) {
                mon.remove();
                System.out.println(mon.len);
                try {
                    sleep(1000);
                } catch(InterruptedException e) {
                    System.out.println("Interrupt error.");
                }
            }
        }
    }

    static class Monitor {
        private int buffer[] = new int[N];
        int len = 0;
        public synchronized void insert(int item) {
            if (len >= N) {
                go_to_sleep();
            }
            buffer[len] = item * len;
            len += 1;
            if (len == 1) {
                notify();
            }
        }

        public synchronized void remove() {
            if (len == 0) {
                go_to_sleep();
            }
            len -= 1;
            if (len == N - 1) {
                notify();
            }
        }

        private void go_to_sleep() {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Wait error.");
            }
        }
    }
    public static synchronized void produce() {
        System.out.println("hello producer");
    }
}