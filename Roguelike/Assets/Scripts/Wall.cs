using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wall : MonoBehaviour
{
    public Sprite damagedSprite;
    public AudioClip[] chopSounds;
    public int hp = 4;

    private SpriteRenderer spriteRenderer;

    void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    public void DamageWall(int damage)
    {
        spriteRenderer.sprite = damagedSprite;
        hp -= damage;
        SoundManager.instance.RandomizeSfx(chopSounds);
        if (hp <= 0)
            gameObject.SetActive(false);
    }
}
