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

  //From mountains to x
  int MToM=0;
  int MToP =0;
  int MToF=0;
  int MToD=0;
  int MToO=0;

  //From plains to x
  int PToM =0;
  int PToP =0;
  int PToF=0;
  int PToD=0;
  int PToO=0;

  //From forests to x
  int FToM =0;
  int FToP=0;
  int FToF=0;
  int FToD=0;
  int FToO=0;

  //From deserts to x
  int DToM =0;
  int DToP=0;
  int DToF=0;
  int DToD=0;
  int DToO=0;

  //From oceans to x
  int OToM =0;
  int OToP=0;
  int OToF=0;
  int OToD=0;
  int OToO=0;


  //TODO FILL IN THE NOT IMPOSSIBLE WEIGHTS
      if(character == 'M'){//The monkey who can just walk and not go in the water or cross the high mountains
        //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000 and then make it so that if a path costs over 1000 it "doesn't exist"
        //From mountains to x
      //From mountains to x
  int MToM=1000;
  int MToP =1000;
  int MToF=1000;
  int MToD=1000;
  int MToO=1000;

  //From plains to x
  int PToM =1000;
  int PToP =0;
  int PToF=0;
  int PToD=0;
  int PToO=1000;

  //From forests to x
  int FToM =1000;
  int FToP=0;
  int FToF=0;
  int FToD=0;
  int FToO=1000;

  //From deserts to x
  int DToM =1000;
  int DToP=0;
  int DToF=0;
  int DToD=0;
  int DToO=1000;

  //From oceans to x
  int OToM =1000;
  int OToP=1000;
  int OToF=1000;
  int OToD=1000;
  int OToO=1000;
        
      }else if(character == 'B'){//The bird that can fly over mountains but that cannot go in the desert
               //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
        //From mountains to x
  int MToM=0;
  int MToP =0;
  int MToF=0;
  int MToD=1000;
  int MToO=0;

  //From plains to x
  int PToM =0;
  int PToP =0;
  int PToF=0;
  int PToD=1000;
  int PToO=0;

  //From forests to x
  int FToM =0;
  int FToP=0;
  int FToF=0;
  int FToD=1000;
  int FToO=0;

  //From deserts to x
  int DToM =0;
  int DToP=0;
  int DToF=0;
  int DToD=1000;
  int DToO=0;

  //From oceans to x
  int OToM =0;
  int OToP=0;
  int OToF=0;
  int OToD=1000;
  int OToO=0;

      }else if(character == 'F'){//The fish that must stay in the water
                //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
      //From mountains to x
  int MToM=1000;
  int MToP =1000;
  int MToF=1000;
  int MToD=1000;
  int MToO=1000;

  //From plains to x
  int PToM =1000;
  int PToP =1000;
  int PToF=1000;
  int PToD=1000;
  int PToO=1000;

  //From forests to x
  int FToM =1000;
  int FToP=1000;
  int FToF=1000;
  int FToD=1000;
  int FToO=1000;

  //From deserts to x
  int DToM =1000;
  int DToP=1000;
  int DToF=1000;
  int DToD=1000;
  int DToO=1000;

  //From oceans to x
  int OToM =0;
  int OToP=0;
  int OToF=0;
  int OToD=0;
  int OToO=0;
        
      }else if(character == 'G'){//The frog that can go everywhere except in the mountains and the desert.
                //For the cannot parts we'll just jack up the edge weights to an extreme amount like 1000
//From mountains to x
  int MToM=1000;
  int MToP =1000;
  int MToF=1000;
  int MToD=1000;
  int MToO=1000;

  //From plains to x
  int PToM =1000;
  int PToP =0;
  int PToF=0;
  int PToD=1000;
  int PToO=0;

  //From forests to x
  int FToM =1000;
  int FToP=0;
  int FToF=0;
  int FToD=1000;
  int FToO=0;

  //From deserts to x
  int DToM =1000;
  int DToP=1000;
  int DToF=1000;
  int DToD=1000;
  int DToO=1000;

  //From oceans to x
  int OToM =0;
  int OToP=0;
  int OToF=0;
  int OToD=0;
  int OToO=0;
        
      }else {
          std::cout<< "You entered an invalid character."<<std::endl;
      }
    return;
}
