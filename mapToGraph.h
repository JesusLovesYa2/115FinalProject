#include"map.h"

void mapToGraph(Map m, char character, Graph* g){//The map is our blueprint, the character will determine the next function to call for edge weights,
                //and the graph is the final output.
  /*
      Monkey: M
      Bird: B
      Fish: F
      Frog: G

      '^' = high mountain
      ' ' = plain
      '"' = forest
      '.' = desert
      '~' = ocean
*/
  //Figure out what all the weights should be
  //Fill in default values and replace later if needed
  //From mountains to x
  int MToM=2;
  int MToP=1;
  int MToF=1;
  int MToD=1;
  int MToO=10;

  //From plains to x
  int PToM=5;
  int PToP=1;
  int PToF=3;
  int PToD=2;
  int PToO=2;

  //From forests to x
  int FToM=6;
  int FToP=2;
  int FToF=3;
  int FToD=2;
  int FToO=5;

  //From deserts to x
  int DToM=10;
  int DToP=2;
  int DToF=3;
  int DToD=2;
  int DToO=3;

  //From oceans to x
  int OToM=10;
  int OToP=3;
  int OToF=3;
  int OToD=3;
  int OToO=1;

      if(character == 'M'){//The monkey who can just walk and not go in the water or cross the high mountains
        //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000 and then make it so that if a path costs over 1000 it "doesn't exist"
        //From mountains to x
        MToM=1000;
        MToP =1000;
        MToF=1000;
        MToD=1000;
        MToO=1000;
      
        //From plains to x
        PToM =1000;
        PToO=1000;
      
        //From forests to x
        FToM =1000;
        FToO=1000;
      
        //From deserts to x
        DToM =1000;
        DToO=1000;
      
        //From oceans to x
        OToM =1000;
        OToP=1000;
        OToF=1000;
        OToD=1000;
        OToO=1000;
              
      }else if(character == 'B'){//The bird that can fly over mountains but that cannot go in the desert (Should we reduce mountain cost?)
               //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
        //From mountains to x
        MToD=1000;
      
        //From plains to x
        PToD=1000;
      
        //From forests to x
        FToD=1000;
      
        //From deserts to x
        DToM =1000;
        DToP=1000;
        DToF=1000;
        DToD=1000;
        DToO=1000;
      
        //From oceans to x
        OToD=1000;

      }else if(character == 'F'){//The fish that must stay in the water
                //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
      //From mountains to x
      MToM=1000;
      MToP =1000;
      MToF=1000;
      MToD=1000;
      MToO=1000;
    
      //From plains to x
      PToM =1000;
      PToP =1000;
      PToF=1000;
      PToD=1000;
      PToO=1000;
    
      //From forests to x
      FToM =1000;
      FToP=1000;
      FToF=1000;
      FToD=1000;
      FToO=1000;
    
      //From deserts to x
      DToM =1000;
      DToP=1000;
      DToF=1000;
      DToD=1000;
      DToO=1000;
    
      //From oceans to x
      OToM =1000;
      OToP=1000;
      OToF=1000;
      OToD=1000;
      //Ocean to ocean is the only thing you shouldn't change
            
      }else if(character == 'G'){//The frog that can go everywhere except in the mountains and the desert.
                //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
      //From mountains to x
      MToM=1000;
      MToP =1000;
      MToF=1000;
      MToD=1000;
      MToO=1000;
    
      //From plains to x
      PToM =1000;
      PToD=1000;
    
      //From forests to x
      FToM =1000;
      FToD=1000;
    
      //From deserts to x
      DToM =1000;
      DToP=1000;
      DToF=1000;
      DToD=1000;
      DToO=1000;
    
      //From oceans to x
      OToM =1000;
      OToD=1000;
        
      }else {
          std::cout<< "You entered an invalid character."<<std::endl;
          //return;//Not sure how to exit here
      }

    //TODO make the graph from the map here
    char holdForTranslate;//Current tile

    char holdForTranslateN;//Tile north
    char holdForTranslateW;//Tile west
    char holdForTranslateE;//Tile east
    char holdForTranslateS;//Tile south
    for(int i =0; i<m.get_height(); i++){//Iterate over the height
        for(int j =0; j<m.get_width(); j++){Iterate over the width
          //Get nodes and surroundings
          holdForTranslate = m.get(j, i);
                                            
          if(j<=0){//Left is out of the map
            holdForTranslateW='!';
          }else{
            holdForTranslateW=m.get(j-1, i);
          }

          if(j>=m.get_width()){//Right is out of the map
            holdForTranslateE='!';
          }else{
            holdForTranslateE=m.get(j+1, i);
          }
                                            
          if(i<=0){//Up is out of the map
            holdForTranslateN='!';
          }else{
            holdForTranslateN=m.get(j, i-1);
          }
                                            
          if(j>=m.get_width()){//Down is out of the map
            holdForTranslateS='!';
          }else{
            holdForTranslateS=m.get(j, i+1);
          }

      //TODO
    }
    return;
}
