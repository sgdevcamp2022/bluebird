using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;


// <빌드 자동화>
//멀티플레이 테스트 환경에서 Build를 하고 일일이 테스트하면 번거롭다
//따라서 스크립트를 작성하여 메뉴 아이템에 등록하면 간단하게 자동으로 빌드를 하여 실행창을 여러개 킬 수 있다. 즉, 빌드 자동화
public class MultiplayersBuildAndRun
{
    [MenuItem("Tools/Run Multiplayer/2 Players")]
    static void PerformWin64Build2()
    {
        PerformWin64Build(2);
    }



    static void PerformWin64Build(int playerCount)
    {
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Standalone, BuildTarget.StandaloneWindows);

        for (int i = 1; i <= playerCount; i++)
        {
            BuildPipeline.BuildPlayer(GetScenePaths(), "Build/Win64/" + GetProjectName() + i.ToString() + "/" + GetProjectName() + i.ToString() + ".exe",
                BuildTarget.StandaloneWindows64, BuildOptions.AutoRunPlayer);
        }
    }

    static string GetProjectName()
    {
        string[] s = Application.dataPath.Split('/');
        //현재 프로젝트 경로 추출. Assst까지
        return s[s.Length - 2];
    }

    static string[] GetScenePaths()
    {
        string[] scenes = new string[EditorBuildSettings.scenes.Length];
        //BuildSetting에 Scene으로 등록한 것이 삽입된다.

        for (int i = 0; i < scenes.Length; i++)
        {
            scenes[i] = EditorBuildSettings.scenes[i].path;
        }


        return scenes;
    }


}
