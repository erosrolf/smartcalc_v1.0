#ifndef ERR_CODES_H
#define ERR_CODES_H

enum error {
  CALC_ERR = -3,
  MEM_ERR = -2,
  ERR = -1,
  OK,
  FEW_ARGS,
  DIV_BY_ZERO,
  TAN_INDEFINED,
  VALIDATE_ERR
};

enum parse_code {
  NUM = 0,
  OPEN_BR = 1,
  LOW_RANG = 2,
  MID_RANG = 3,
  HIGH_RANG = 4,
  TOP_RANG = 5,
  CLOSE_BR = 6,
  STR_DONE = 7
};

enum funcs {
  COS = 'c',
  SIN = 's',
  TAN = 't',
  ACOS = 'C',
  ASIN = 'S',
  ATAN = 'T',
  SQRT = 'q',
  LN = 'n',
  LOG = 'g'
};

#endif // ERR_CODES_H
