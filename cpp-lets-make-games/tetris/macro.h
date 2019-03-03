#pragma once

// 메모리 해제 기능
#define SAFE_DELETE(p) if (p) { delete p; p =  NULL; }
