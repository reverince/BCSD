using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public static GameManager instance = null;

    public BoardManager boardManager;
    public float levelStartDelay = 2f;
    public float turnDelay = 0.1f;
    public int playerFoodPoint = 100;
    [HideInInspector] public bool playersTurn = true;

    private int level = 1;
    private Text levelText;
    private GameObject levelImage;
    private List<Enemy> enemies;
    private bool doingSetup;
    private bool enemiesMoving;

    void Awake()
    {
        if (instance == null)  // 싱글톤
            instance = this;
        else
            Destroy(gameObject);

        DontDestroyOnLoad(gameObject);  // 씬이 바뀌어도 GameManager는 파괴하지 않음
        boardManager = GetComponent<BoardManager>();
        enemies = new List<Enemy>();
        InitializeGame();
    }

    void Update()
    {
        if (doingSetup || playersTurn || enemiesMoving) return;

        StartCoroutine(MoveEnemies());
    }

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.AfterSceneLoad)]
    static public void CallbackInitialization()
    {
        SceneManager.sceneLoaded += OnSceneLoaded;
    }

    static private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        instance.level++;
        instance.InitializeGame();
    }

    private void InitializeGame()
    {
        doingSetup = true;
        levelImage = GameObject.Find("Level Image");
        levelText = GameObject.Find("Level Text").GetComponent<Text>();
        levelText.text = $"DAY {level}";
        Invoke("HideLevelImage", levelStartDelay);

        enemies.Clear();
        boardManager.SetupScene(level);
    }

    private void HideLevelImage()
    {
        levelImage.SetActive(false);
        doingSetup = false;
    }

    private IEnumerator MoveEnemies()
    {
        enemiesMoving = true;
        yield return new WaitForSeconds(turnDelay);
        if (enemies.Count == 0)
        {
            yield return new WaitForSeconds(turnDelay);
        }

        for (int i = 0; i < enemies.Count; ++i)
        {
            enemies[i].MoveEnemy();
            yield return new WaitForSeconds(enemies[i].moveTime);
        }

        enemiesMoving = false;
        playersTurn = true;
    }

    public void AddEnemy(Enemy script)
    {
        enemies.Add(script);
    }

    public void GameOver()
    {
        levelText.text = $"You survived {level.ToString()} day{(level == 1 ? "" : "s")}";
        levelImage.SetActive(true);
        enabled = false;
    }
}
