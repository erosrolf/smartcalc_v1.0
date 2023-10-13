#ifndef ERR_CODES_H
#define ERR_CODES_H
enum error { MEM_ERR = -2, ERR = -1, OK, FEW_ARGS, DIV_BY_ZERO };
enum parse_code {
  NUM = 10,
  // OPER > 0
  OPEN_BR = 1,
  LOW_RANG = 2,
  MID_RANG = 3,
  TOP_RANG = 4,
  CLOSE_BR = 5,
  STR_DONE = 6,
};
#endif
