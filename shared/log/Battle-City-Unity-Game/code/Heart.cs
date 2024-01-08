using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//基地的方法
public class Heart : MonoBehaviour
{
    private SpriteRenderer sr;//破坏方法
    public GameObject explosionPrefab;//爆炸特效
    public Sprite BrokenSprite;//破坏的图片
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();//得到他的组件
    }

    public void Die()
    {
        sr.sprite = BrokenSprite;//更换图片
        Instantiate(explosionPrefab, transform.position, transform.rotation);
        PlayerManager.Instance.isDefeat = true;//基地被破坏
    }
}
