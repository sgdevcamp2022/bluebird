using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using static Define;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
//플레이어가 goal 하면 stagenum을 검사한다. 만약 최종 스테이지가 아니면 don't destory on load. 최종스테이지면 destroy
//goal 못하면 바로 destory. don't destory on load 한건 다음 스테이지에서 스폰위치에 소환
public class MyPlayerController : PlayerController
{
    //public  bool serverCommunication = false;
    GameScene gamescene;
    GameManager gamemanager;
    bool inMenu = false;
    bool inGoal = false;
    protected override void Init()
    {
        base.Init();
        gamescene = GameObject.Find("GameScene").GetComponent<GameScene>();
        gamemanager = GameObject.Find("GameManager").GetComponent<GameManager>();
    }
    protected override void UpdateController()
    {
        switch (State)
        {
            case BirdState.Idle:
                GetInput();
                break;
            case BirdState.Moving:
                GetInput();
                break;
            case BirdState.Jumping:
                GetInput();
                break;
        }
        base.UpdateController();
    }
    void GetInput()
    {
        if (gamescene.CheckStartGame() && !inGoal)
        {
            if (transform.position.y < -1)
            {
                transform.position = new Vector3(0.1f, 0.2f, 29f);
                transform.rotation = Quaternion.Euler(0, 180f, 0f);
            }
            if (State == BirdState.Jumping && isJumping == false)
            {
                State = BirdState.Idle;
            }
            float h = 0.0f;
            float v = 0.0f;
            h = Input.GetAxis("Horizontal");
            v = Input.GetAxis("Vertical");
            pressedJump = Input.GetKeyDown(KeyCode.Space);
            moveVec = new Vector3(h, 0f, v).normalized;
            if (pressedJump && !isJumping)
            {
                State = BirdState.Jumping;
            }
            if (isJumping && State == BirdState.Jumping)
            {
                bool SlideBtn = Input.GetMouseButtonDown(1);
                if (SlideBtn)
                    isSliding = true;
                else
                    isSliding = false;
            }
            //esc를 누르면 menupanel이 활성화되고 나의 키보드 시스템은 정지된다.
            //계속하기를 누르면 menupaneel이 비활성화되고, 나의 키보드 시스템은 다시 시작된다.
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                inMenu = true;
                gamemanager.ActiveMenu();
            }
        }
        //  Debug.Log("State : " + State + " isJumping: " + isJumping + " moveVec: " + moveVec + " pressedJump: " + pressedJump + "isSliding" + isSliding) ;
    }
    //Idle로 계속 남을지, 다른 상태로 넘어갈지를 판단.
    protected override void UpdateIdle()
    {
        if (moveVec.x != 0 || moveVec.z != 0)
        {
            State = BirdState.Moving;
            return;
        }
    }
    //플레이어가 먼저 이동하고 좌표를 보냄, 플레이어의 지상에서의 움직임을 제어한다.
    protected override void UpdateMoving()
    {
        prevVec = transform.position;
        Vector3 movementDirection = Quaternion.AngleAxis(cam.transform.eulerAngles.y, Vector3.up) * moveVec;
        movementDirection.Normalize();
        transform.rotation = Quaternion.Euler(0f, cam.transform.eulerAngles.y, 0f);
        transform.position += movementDirection * speed * Time.deltaTime;
        UpdateAnimation();
        if (prevVec == transform.position)
        {
            State = BirdState.Idle;
            UpdateAnimation();
            Move playerMove = new Move()
            {
                Id = playerId,
                Time = Managers.Network.TICK,
                Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                State = PlayerState.Idle,
            };
            Managers.Network.Send(playerMove, INGAME.PlayerMove);
        }
        else if (prevVec != transform.position)
        {
            Move playerMove = new Move()
            {
                Id = playerId,
                Time = Managers.Network.TICK,
                Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                State = PlayerState.Move,
            };
            Managers.Network.Send(playerMove, INGAME.PlayerMove);
        }
    }
    protected override void UpdateJumping()
    {
        prevVec = transform.position;
        Vector3 movementDirection = Quaternion.AngleAxis(cam.transform.eulerAngles.y, Vector3.up) * moveVec;
        movementDirection.Normalize();
        transform.rotation = Quaternion.Euler(0f, cam.transform.eulerAngles.y, 0f);
        //바닥에 착지해있는 상태라면 점프 수행
        if (!isJumping && State == BirdState.Jumping)
        {
            Jump();
            isJumping = true;
        }
        //아직까지 공중에 떠있다면 계속해서 패킷 전송
        if (isJumping && State == BirdState.Jumping)
        {
            UpdateAnimation();
            if (isSliding)
                animator.SetBool("isSlide", true);
            transform.position += movementDirection * speed * Time.deltaTime;
        }
        if (!isSliding)
        {
            Move playerMove = new Move()
            {
                Id = playerId,
                Time = Managers.Network.TICK,
                Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                State = PlayerState.Jump,
            };
            Managers.Network.Send(playerMove, INGAME.PlayerMove);
        }
        else
        {
            Move playerMove = new Move()
            {
                Id = playerId,
                Time = Managers.Network.TICK,
                Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                State = PlayerState.Slide,
            };
            Managers.Network.Send(playerMove, INGAME.PlayerMove);
        }
    }
    void Jump()
    {
        if (!isJumping && State == BirdState.Jumping)
        {
            rigid.AddForce(Vector3.up * jumpPower, ForceMode.Impulse);
            animator.SetTrigger("doJump");
        }
        else
            return;
    }
    void UpdateAnimation()
    {
        switch (State)
        {
            case BirdState.Idle:
                animator.SetBool("MoveForward", false);
                animator.SetBool("inAir", false);
                animator.SetBool("isSlide", false);
                break;
            case BirdState.Moving:
                animator.SetBool("MoveForward", true);
                animator.SetBool("inAir", false);
                animator.SetBool("isSlide", false);
                break;
            case BirdState.Jumping:
                animator.SetBool("MoveForward", false);
                animator.SetBool("inAir", true);
                break;
        }
    }
    //Goal 하면 invisible, 카메라만 움직일 수 있게 만든다.
    //게임 시간 초과 or 모든 인원이 결승선을 통과해 게임이 종료되면 통과한 플레이어를 다음 Scene으로 옮긴다.
    //다음 Scene으로 옮겨진 Player들은 Random 한 출반선안의 Random Position에 스폰된다.
    protected override void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Victory Ground") && !inGoal)
        {
            State = BirdState.Idle;
            isJumping = false;
            isSliding = false;
            inGoal = true;
            UpdateAnimation();
            PlayerGoalData pkt = new PlayerGoalData
            {
                Id = playerId,
                Success = true,
            };
            Managers.Network.Send(pkt, INGAME.PlayerGoal);
            clearStageNum++;
            inGoal = true;
            this.transform.GetChild(0).gameObject.SetActive(false);
        }
        if (collision.gameObject.CompareTag("Ground"))
        {
            if (isJumping)
            {
                //Debug.Log("collisionGround");
                State = BirdState.Idle;
                isJumping = false;
                isSliding = false;
                UpdateAnimation();
                Move playerMove = new Move()
                {
                    Id = playerId,
                    Time = Managers.Network.TICK,
                    Position = new Vector { X = transform.position.x, Y = transform.position.y, Z = transform.position.z },
                    Rotation = new Vector { X = transform.eulerAngles.x, Y = transform.eulerAngles.y, Z = transform.eulerAngles.z },
                    State = PlayerState.Idle,
                };
                Managers.Network.Send(playerMove, INGAME.PlayerMove);
            }
        }
    }
}
/*
 //서버가 좌표를 보내주면 이동하는 형식
        if (serverCommunication)
        {
            PlayerState prevState = State;
            prevVec = transform.position;
            //moveVec = transform.position + (moveVec * speed * Time.deltaTime);
            if (prevState != State || prevVec != moveVec)
            {
                Move playerMove = new Move()
                {
                    Id = playerId,
                    Position = new Vector { X = moveVec.x, Y = moveVec.y, Z = moveVec.z },
                    Rotation = new Vector { X = moveVec.x, Y = moveVec.y, Z = moveVec.z },
                };
                Managers.Network.Send(playerMove, INGAME.PlayerMove);
            }
            if (playerInfo.Position.X == prevVec.x && playerInfo.Position.Z == prevVec.z)
            {
                State = PlayerState.Idle;
                return;
            }
            else
            {
                State = PlayerState.Moving;
                moveVec = new Vector3(playerInfo.Position.X, playerInfo.Position.Y, playerInfo.Position.Z);
                transform.position = moveVec;
                Debug.Log("Player:UpdateMoving : moveVec    " + moveVec + "State :" + State);
            }
        }
        */