/* BMI Calculator */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    float ht, wt, bmi, htl, hth, wtl, wth;
    
    printf("Enter -1 if you want to see the ideal range\n"); 
    printf("Enter height(cm): ");
    scanf("%f", &ht);
    printf("Enter weight(kg): ");
    scanf("%f", &wt);
    
    bmi = 10000*wt/ht/ht;
    htl = 100*sqrt(wt/24);
    hth = 100*sqrt(wt/18.5);
    wtl = 18.5/10000*ht*ht;
    wth = 24/10000*ht*ht;
    
    if (wt<0 && wt!=-1 || ht<0 && ht!=-1) {
       printf("Don't play around with this program!\n\n\n");
       main();
    }
    
    if (wt == -1)
       printf("\n妳體重最好在 %.2fkg 和 %.2fkg 之間...超過你就慘了!!\n\n\n", wtl, wth);
    else if (ht == -1)
       printf("\n妳這體重的話，正常身高範圍是在 %.2fcm 到%.2fcm...妳應該已經超過了..不要再長了..\n\n\n", htl, hth); 
    else {
       printf("\nyour BMI score is %.2f", bmi);
    
       if (bmi < 16)
          printf("...妳有病喔!!瘦到皮包骨了還不吃東西!?  快去把妳家冰箱清乾淨!!\n\n\n");
       else if (bmi<18.5)
          printf("...體重過輕喔..吃多一點吧!\n\n\n");
       else if (bmi<24)
          printf("...妳騙人吧!!?  妳有這麼正常?\n\n\n");
       else if (bmi<27)
          printf("...嘿嘿嘿..妳過重喔!! 該注意了!\n\n\n");
       else if (bmi<30)
          printf("...恩..輕度肥胖...現在不是楊貴妃時代 請還是保持中等身材!\n\n\n");
       else if (bmi<35)
          printf("...中度肥胖!! 妳再吃嘛! 把零食收起來!! \n\n\n");
       else if (bmi>35)
          printf("...OMG! 妳什麼時候變長成這樣了!!? 給我十天不准吃東西! 然後出去跑步!! \n\n\n");
    }
    main();

    system("pause");
    return 0;
}
