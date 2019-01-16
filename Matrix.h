//
// Created by tomer on 1/13/19.
//

#ifndef FLIGTSIMPROJ2_MATRIX_H
#define FLIGTSIMPROJ2_MATRIX_H

#include "ISearchable.h"
using namespace std;

class Node{
public:
    int i;
    int j;

    Node(int x, int y){
        this->i=x;
        this->j=y;
    }

    bool operator==(Node& rhs){
        bool ans= (rhs.i==i && rhs.j==j);
        return ans;
    }
};

class Matrix : public ISearchable<Node>{
private:
    int **matrix;
    int row;
    int col;
    Node* start;
    Node*  goal;

public:
    // we get here a specified starting node and goal node
    Matrix(int **matrix, int row, int col, Node* start, Node* goal);
    // we get here a specified starting point and starting goal by int
    Matrix(int **matrix, int row, int col, int i_start, int j_start, int i_goal, int j_goal);
    //there aren't any starting points and goals
    Matrix(int **matrix, int row, int col);
    State<Node>* stateGenarator(int i, int j, State<Node>* pre);
    State<Node>* getInitialState() override;
    set<State<Node>*> getAllPossibleStates(State<Node>* currState) override;
    bool isGoal(State<Node>* currState) override;
    virtual string getStrRepresentation();
    ~Matrix();
};


#endif //FLIGTSIMPROJ2_MATRIX_H
