using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Player : MovingObject
{
    public Text footText;
    public AudioClip[] moveSounds;
    public AudioClip[] eatSounds;
    public AudioClip[] drinkSounds;
    public AudioClip gameOverSound;
    public int wallDamage = 1;
    public int pointPerFood = 10;
    public int pointPerSoda = 20;
    public float restartLevelDealy = 1f;
    

    private Animator animator;
    private int food;

    protected override void Start()
    {
        animator = GetComponent<Animator>();
        food = GameManager.instance.playerFoodPoint;
        footText.text = $"Food: {food.ToString()}";

        base.Start();
    }

    private void OnDisable()
    {
        GameManager.instance.playerFoodPoint = food;
    }

    void Update()
    {
        if (!GameManager.instance.playersTurn) return;

        int horizontal = (int)Input.GetAxisRaw("Horizontal");
        int vertical = (int)Input.GetAxisRaw("Vertical");

        if (horizontal != 0)
            vertical = 0;
        if (horizontal != 0 || vertical != 0)
        {
            AttemptMove<Wall>(horizontal, vertical);
        }
    }

    protected override void AttemptMove<T>(int xDir, int yDir)
    {
        food--;
        footText.text = $"Food: {food.ToString()}";

        base.AttemptMove<T>(xDir, yDir);

        if (Move(xDir, yDir, out RaycastHit2D hit))
        {
            SoundManager.instance.RandomizeSfx(moveSounds);
        }

        IsGameOver();
        GameManager.instance.playersTurn = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Exit"))
        {
            Invoke("Restart", restartLevelDealy);
            enabled = false;
        }
        else if (collision.CompareTag("Food"))
        {
            AddFood(pointPerFood);
            SoundManager.instance.RandomizeSfx(eatSounds);
            collision.gameObject.SetActive(false);
        }
        else if (collision.CompareTag("Soda"))
        {
            AddFood(pointPerSoda);
            SoundManager.instance.RandomizeSfx(drinkSounds);
            collision.gameObject.SetActive(false);
        }
    }

    protected override void OnCantMove<T>(T component)
    {
        Wall hitWall = component as Wall;
        hitWall.DamageWall(wallDamage);
        animator.SetTrigger("playerChop");
    }

    private void Restart()
    {
        SceneManager.LoadScene(0);  // 현재 씬 로드
    }
    
    private void AddFood(int add)
    {
        food += add;
        footText.text = $"Food: {food.ToString()} + {add.ToString()}";
    }

    public void LossFood(int loss)
    {
        animator.SetTrigger("playerHit");
        food -= loss;
        footText.text = $"Food: {food.ToString()} - {loss.ToString()}";
        IsGameOver();
    }

    private void IsGameOver()
    {
        if (food <= 0)
        {
            SoundManager.instance.RandomizeSfx(gameOverSound);
            SoundManager.instance.musicSource.Stop();
            GameManager.instance.GameOver();
        }
    }
}
