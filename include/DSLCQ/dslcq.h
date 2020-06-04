#ifndef _DSLCQ_H
#define _DSLCQ_H

#include "../templates/LinkedList.h"
#include "../DSSV/dssv.h"

class LopCQ {
public:
  char * MALOP;
  DanhSachSinhVien * DSSV;
  
  //** Constructor 
  LopCQ(char *);
  LopCQ() {;}
};

class DanhSachLopCQ: public LinkedList<LopCQ> {
private:
  char db[32] = "../database/dslcq.d";

public:
  LopCQ get_lcq(char *);
  DanhSachSinhVien * get_dssv(char *);
  SinhVien * search_sv(char *);
  LopCQ get_by_index(int index);
  void save();
  void load();
};

#endif
