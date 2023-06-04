public class Main {
    static final int PHI_NUM = 5;
    static Phil[] phils = new Phil[PHI_NUM];
    static PhilThread[] philThreads = new PhilThread[PHI_NUM];
    static Monitor monitor = new Monitor();

    static {
        for (int i = 0; i < phils.length; ++i) {
            phils[i] = new Phil(i);
            philThreads[i] = new PhilThread(i);
        }
    }

    public static void main(String[] args) {
        for (PhilThread philThread : philThreads) {
            philThread.start();
        }
    }

    static class Monitor {      // 作为 phils 的管程
        boolean isThinking(int i) {
            return phils[i].state == Phil.State.Thinking;
        }

        synchronized void eat(int id) {
            while (!(isThinking(left_phil(id).id) && isThinking(right_phil(id).id))) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    System.out.println("Wait error.");
                }
            }
            phils[id].state = Phil.State.Eating;
            System.out.println(id + ": eating...");
        }

        synchronized void think(int id) {
            phils[id].state = Phil.State.Thinking;
            System.out.println(id + ": thinking...");
            if (isThinking(left_phil(id).id)) {
                notify();
            }
            if (isThinking(right_phil(id).id)) {
                notify();
            }
        }

        Phil left_phil(int id) {
            return phils[id == 0 ? PHI_NUM - 1 : (id - 1)];
        }

        Phil right_phil(int id) {
            return phils[id == PHI_NUM - 1 ? 0 : (id + 1)];
        }
    }

    static class PhilThread extends Thread {

        public final int id;

        public PhilThread(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            while (true) {
                monitor.think(id);
                try {
                    sleep((long) (Math.random() * 1000));
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                monitor.eat(id);
                try {
                    sleep((long) (Math.random() * 1000));
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    static class Phil { // 哲学家
        enum State {
            Thinking,
            Eating
        }

        State state = State.Thinking;
        final int id;

        public Phil(int id) {
            super();
            this.id = id;
        }

    }
}

