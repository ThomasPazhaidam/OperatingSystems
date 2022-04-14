/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

import java.util.logging.Level;
import java.util.logging.Logger;

public class DiningPhilosophers {
    final static int N = 5;
    final static Semaphore mutex = new Semaphore(1);
    final static Philosopher[] philosophers = new Philosopher[N];
    public static int cmplt = 0;
    
    public static void main(String[] args) {
        
        for (int i = 0; i < N; i++) {
            philosophers[i] = new Philosopher(i);
        }
        
        for (int i=0; i<N;i++) {
            Thread p = new Thread(philosophers[i]);
            p.start();
        }
    }
    
    public static class Philosopher extends Thread {
        private enum State {THINKING, HUNGRY, EATING};
        public static int count = 0;
        private final int id;
        public State state;
        private final Semaphore currentstate;
        private int done = 0;
        
        Philosopher(int id) {
            this.id = id;
            currentstate = new Semaphore(0);
            state = State.THINKING;
        }
       
        private Philosopher right() {
            return philosophers[(id + 1) % N];
        }
       
        private Philosopher left() {
            if(id==0){
               return philosophers[N-1];
            }else{
               return philosophers[id-1]; 
            }
        }
        
        @Override
        public void run() {
            try {
                while (cmplt < N) {
                    print();
                    count++;
                    
                    switch(state) {
                        case THINKING:
                            task();
                            
                            if (done != 1) {
                                mutex.down();
                                state = State.HUNGRY;
                            } else {
                                System.out.println("Philosopher " + this.id + " completed his dinner");
                            }
                            break;
                        case HUNGRY:
                            getfork(this);
                            mutex.up();
                            currentstate.down();
                            state = State.EATING;
                            break;
                        case EATING:
                            cmplt++;
                            task();
                            mutex.down();
                            state = State.THINKING;
                            putfork(this);
                            mutex.up();
                            this.done = 1;
                            break;
                    }
                }
                if (this.id == 0) {
                    task();
                    System.out.println("Till now number of philosophers completed dinner are " + cmplt);
                }
            } 
            catch(InterruptedException e) {
                System.out.println(e);
            }
        }
        static private void getfork(Philosopher p) {
            if (p.left().state != State.EATING && p.right().state != State.EATING && p.state == State.HUNGRY) {
                p.state = State.EATING;
                p.currentstate.up();
            }
        }
        
        static private void putfork(Philosopher p) {
            getfork(p.left());
            getfork(p.right());
        }
        
        private void task() {
            try {
                Thread.sleep((long)Math.round(Math.random() * 5000));
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        
        private void print() {
            if (state != State.HUNGRY) {
                System.out.println("Fork " + (this.id+1) + " taken by Philosopher " + (this.id+1));
            }
            if (state == State.EATING) {
                System.out.println("Til now the number of philosophers completed dinner are " + cmplt);
            }
            if (state == State.HUNGRY) {
                System.out.println("Philosopher " + (this.id+1) + " waiting for Fork " + (left().id+1));
            }
        }
    }
}