class Element{
private:
    int id = 0;
public:
    Element(int i){
        this->id = i;
    }
    int getIconId(){
        return this->id;
    }
};
class Map{
private:
    int sizeX = 64;
    int sizeY = 64;
    Element map[sizeX][sizeY];
public:
    Map(){
        for(int i=0; i<sizeX;i++){
            for(int j=0;j<sizeY;j++){
                this->map[i][j] = new Element(0);
            }
        }
    }
    int** getIconIds(){
      int** array2D = 0;
      array2D = new int*[sizeX];
      for (int i = 0; i < sizeX; i++){
            array2D[i] = new int[sizeY];
            for (int j = 0; j < sizeY; j++){
                  array2D[i][j] = this->map[i][j].getIconId();
            }
      }
      return array2D;
    }
};