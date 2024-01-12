public class Health {
  private int health = 100;

  synchronized void increase(int amount) {
    health += amount;
  }

  synchronized void decrease(int amount) {
    health -= amount;
  }
}