#pragma once

//BASE MACRO
constexpr auto BUFFER_SIZE = 20000;
constexpr auto CLIENT = 1;
constexpr auto SERVER = 2;
constexpr auto SERVER_IP = "10.30.10.209";

constexpr auto MAX_PARTY_COUNT = 4;

//Scene
constexpr auto LOGIN_SCENE = 1000;
constexpr auto LOGIN_SCENE_ING = 1001;
constexpr auto LOGIN_SCENE_FAIL = 1002;
constexpr auto LOGIN_SCENE_SUCCESS = 1003;

constexpr auto LOBBY_SCENE = 2000;

constexpr auto STAGE_SELECT_SCENE = 3000;
constexpr auto STAGE_LOADING_SCENE = 3001;
constexpr auto STAGE_PLAY_SCENE = 4000;

//TCP DATA
constexpr auto TCP_LOGIN_MESSAGE = 100;

constexpr auto TCP_SIMPLE_DATA_MESSAGE = 200;

constexpr auto TCP_PARTY_MAIN = 300;
constexpr auto TCP_PARTY_MAKE = 100;
constexpr auto TCP_PARTY_INVITE = 101;
constexpr auto TCP_PARTY_ACCEPT = 102;
constexpr auto TCP_PARTY_INFO = 103;
constexpr auto TCP_PARTY_EXIT = 105;

constexpr auto TCP_STAGE_MAIN = 400;
constexpr auto TCP_ENTER_STAGE_SELECT = 100;

//UDP DATA
constexpr auto UDP_PARTY_INFO = 100;
constexpr auto UDP_OBJECT_MAIN = 200;
