using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public float speed;
    public Text scoreText;
    public Text winText;
    public int winScore;

    private Rigidbody2D rb;
    private int m_score;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        SetScore(0);
        winText.text = "";
    }

    // Use FixedUpdate when using forces
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");
        Vector2 movement = new Vector2(moveHorizontal, moveVertical);
        rb.AddForce(movement * speed);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("Pickup"))
        {
            collision.gameObject.SetActive(false);
            SetScore(m_score+1);
        }
    }

    void SetScore(int score)
    {
        m_score = score;
        scoreText.text = $"{m_score.ToString()}점";
        if (m_score >= winScore)
        {
            winText.text = "클리어!";
        }
    }
}
