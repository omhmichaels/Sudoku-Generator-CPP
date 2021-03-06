#include "SudokuSolver.h"

int SudokuSolver::DFS(GenSudoku &obj, bool end) {
    if(__abort__)
        throw std::exception();

    obj.moveNext();
    if( obj.isIndexLast() )
        return 1;

    int sum = 0;

    std::vector<char> v = obj.getAvailable();
    if(v.size() == 0)
        return 0;

    int i = obj.getIndex();
    for(char item : v) {
        obj.setAtIndex(item);
        int ret = DFS(obj, end);
        if(ret>0) {
            if(!end)
                return 1;
            else
                sum+=ret;
        }
        obj.setIndex(i);
        obj.setAtIndex(0);
    }
    return sum;
}

bool SudokuSolver::DFSLV(GenSudoku &obj,long start, int max,  int maxSol) {
    if(__abort__)
        throw std::exception();

    obj.moveNext();

    if( (time(0)-start)>=max && max>0)
        return false;

    if(obj.isIndexLast()) {
        if(cSol < maxSol) {
            if(lastField)
                delete(lastField);
            lastField = new GenSudoku(obj);
        }
        return true;
    }

    std::vector<char> v = obj.getAvailable();
    if(v.size() == 0)
        return 0;

    int i = obj.getIndex();
    for(char item : v) {
        obj.setAtIndex(item);
        if(DFSLV(obj, start, max, maxSol))
            cSol++;
        obj.setIndex(i);
        obj.setAtIndex(0);
        if(cSol >= maxSol)
            return 0;
    }
    return 0;
}
