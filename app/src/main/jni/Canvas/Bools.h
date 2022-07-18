#ifndef BOOLS_H
#define BOOLS_H

#include <jni.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>

bool isESP = false;

bool isPlayerLine2 = false;

bool isPlayerName = false;

bool isPlayerDist = false;

bool isPlayerHealth = false;

bool isTeamMateShow = false;

bool isPlayerBox = false;

bool isPlayerLine = false;

bool isPlayer360 = false;

bool isPlayerDistance = false;

bool isCrosshair = false;

bool isDrawCircle = false;

bool isPlayerCount = false;

Color LineColorBranco = Color::White();

Color LineColorPreto = Color::Black();

Color CrossColor = Color::White();

Color CircleColor = Color::White();

int LineColor = 0;

float CrossSize = 42;

float playerTextSize = 12;

float CircleSize = 22;

float Linesize = 1;

#endif
