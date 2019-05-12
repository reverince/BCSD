using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{
    public GameObject hazard;
    public Text scoreText;
    public Text gameOverText;
    public Text restartText;
    public Vector3 spawnValues = new Vector3(7.0f, 0.0f, 18.0f);
    public int hazardCount = 10;
    public float spawnWait = 0.5f;
    public float startWait = 1.0f;
    public float waveWait = 2.0f;

    int score;
    bool gameOver;
    bool restart;

    void Start()
    {
        score = 0;
        gameOver = false;
        gameOverText.enabled = false;
        restart = false;
        restartText.enabled = false;
        UpdateScore();

        StartCoroutine(SpawnWaves());
    }

    void Update()
    {
        if (restart)
        {
            if (Input.GetKeyDown(KeyCode.R))
            {
                SceneManager.LoadScene(0);
            }
        }
    }

    IEnumerator SpawnWaves()
    {
        yield return new WaitForSeconds(startWait);
        while (true)
        {
            for (int i = 0; i < hazardCount; i++)
            {
                Vector3 spawnPosition = new Vector3(Random.Range(-spawnValues.x, spawnValues.x), spawnValues.y, spawnValues.z);
                Quaternion spawnRotation = Quaternion.identity;
                Instantiate(hazard, spawnPosition, spawnRotation);
                yield return new WaitForSeconds(spawnWait);

                
            }
            yield return new WaitForSeconds(waveWait);

            if (gameOver)
            {
                restartText.enabled = true;
                restart = true;
                break;
            }
        }
    }

    public void AddScore(int amount)
    {
        score += amount;
        UpdateScore();
    }

    void UpdateScore()
    {
        scoreText.text = "점수: " + score + "점";
    }

    public void GameOver()
    {
        gameOver = true;
        gameOverText.enabled = true;
    }
}
