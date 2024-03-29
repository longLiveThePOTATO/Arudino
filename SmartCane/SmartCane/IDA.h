//Intersection Detection Algorithm_교차로 감지 알고리즘


float detectingI(float a, float b1, float b2, float c){
  if(a>400 && b>400> && c>500){
    return 0;
  }
  else if(b1>400){
    if(a<c && a<400){
      if((b2-a)^2>4*a){
        return 1;   //교차로
      }
    }
    else if(c<a && c<400){
      if((b2-c)^2>4*c){
        return 1;   //교차로
      }
    }

    
  }

}
