#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/queue/MyStack.h"
#include "../../includes/binary_files/file_record.h"

#include "../../includes/Tokens/Tokens.h"
#include "../../includes/Tokens/Logical.h"
#include "../../includes/Tokens/LParen.h"
#include "../../includes/Tokens/Operator.h"
#include "../../includes/Tokens/Relational.h"
#include "../../includes/Tokens/ResultSet.h"
#include "../../includes/Tokens/RParen.h"
#include "../../includes/Tokens/TokenStr.h"

#include <vector>
#include <queue>

using namespace std;
typedef Map<string, string> map_ss;
typedef MMap<string, string> mmap_ss;

typedef Map<string, long> map_sl;
typedef MMap<string, long> mmap_sl;

typedef vector<string> vectorstr;
typedef vector<long> vectorlong;
typedef Queue<string> queuestr;
#endif