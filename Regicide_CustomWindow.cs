using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class Regicide_CustomWindow : EditorWindow
{

    float buttonWidth = 80;
    float buttonHeight = 80;

    static string tag;

    float enemyHealth;
    float enemyDamage;

    //Create a custom window
    [MenuItem("Engines 5/Enemy Editor")]

    public static void ShowWindow()
    {
        //Creates window for randomize enemy stats
        GetWindow<Regicide_CustomWindow>("Randomize Enemy Stats");
    }

    private void OnGUI()
    {        
        //Assign tags
        GUILayout.Label("Tags", EditorStyles.boldLabel);
        tag = EditorGUILayout.TagField(tag);
        if (GUILayout.Button("SetTag"))
        {
            foreach (GameObject gameobj in Selection.gameObjects)
            {
                gameobj.tag = tag;
            }
        }

        //Enemy Stats
        GUILayout.Label("Enemy Stats", EditorStyles.boldLabel);
        GUILayout.BeginHorizontal();
        //Generate Enemy Health Button
        if (GUILayout.Button(Resources.Load<Texture>("Picture/01"), GUILayout.Width(buttonWidth), GUILayout.Height(buttonHeight)))
        {
            enemyHealth = Random.Range(30, 100);
            Debug.Log("Generated Health: " + enemyHealth);
        }

        //Generate Enemy Damage Button
        if (GUILayout.Button(Resources.Load<Texture>("Picture/02"), GUILayout.Width(buttonWidth), GUILayout.Height(buttonHeight)))
        {
            enemyDamage = Random.Range(10, 50);
            Debug.Log("Attacking Damage: " + enemyDamage);
        }
            GUILayout.EndHorizontal();

        //Spawning number of enemies
        GUILayout.Label("Instantiate Enemies", EditorStyles.boldLabel);
        GUILayout.BeginHorizontal();
        if (GUILayout.Button(Resources.Load<Texture>(""), GUILayout.Width(buttonWidth), GUILayout.Height(buttonHeight)))
        {
            Instantiate(Resources.Load("Cube"));
        }
    }
}
