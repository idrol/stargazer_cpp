#include "EditorApplication.h"
#include "EditorUpdateHandler.h"
#include <iostream>
#include <stdio.h>
#include "../Engine/StargazerEngine.h"
#include "../Engine/Level/Level.h"
#include "EditorLevel.h"

int main() {
	freopen("log.txt","w",stdout);
	new EditorApplication(new EditorUpdateHandler());
}