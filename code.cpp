// This project is intented to generate a time table for an individual according to the courses chosen by the person.  

#include<bits/stdc++.h>
#include<fstream>

using namespace std;

// I tried to make the time table generator as memory and time optimized as I could and so I completed this project with only approx 150 lines of code. 

/* This time table generator gives the student flexibility to choose courses from any semester they want without worrying about the timings 
    as the code will automatically prevent the student from taking a course with the same time schedule.
*/

// Professors are distributer among all courses with an algorithm such that total number professors is equal to half of that of total number of courses.

string slots[5][9] = {{"T1", "A", "B", "D", "F", "LB", "L1", "L1", "L1"}, {"T2", "A", "C", "D", "F", "LB", "L2", "L2", "L2"}, {"T3", "A", "C", "E", "G", "LB", "L3", "L3", "L3"}, {"T4", "B", "C", "E", "G", "LB", "L4", "L4", "L4"}, {"T5", "B", "D", "F", "G", "LB", "L5", "L5", "L5"}}; 
int l, m, n;
string tc[7] = {"A", "B", "C", "D", "E", "F", "G"};
string lc[5] = {"L1", "L2", "L3", "L4", "L5"};
string tutc[5] = {"T1", "T2", "T3", "T4", "T5"};

// STL Maps have been used to make the code more efficient and occupy less memory.

map<string, string> tt;
map<string, string> prof;

/* Matrix has been used in the algorithm for alotting courses such that each row contains courses in the same timing slot and
   each column contains course for each semester. The student can also take minor and SA courses along with dropped courses of previous semester if any.
*/

string theorycourses[7][10] = {{"CH101", "BT101", "DA231", "DA221", "DA301","DA311", "DA401", "DA411", "DA672", "None"}, 
                            {"EE101", "CS101", "DA241", "DA222", "DA302","DA312", "DA402", "DA412", "DA547", "None"},
                            {"MA101", "MA102", "DA242", "DA223", "DA303","DA313", "DA403", "DA413", "DA641", "None"},
                            {"CE101", "ME101", "DA211", "DA224", "DA304","DA314", "DA404", "DA414", "DA621", "None"},
                            {"PH101", "PH102", "DA251", "DA225", "DA305","DA315", "DA405", "DA415", "DA622", "None"},
                            {"SA101", "SA102", "SA103", "SA104", "SA105", "SA106", "SA107", "SA108", "SA109", "None"},
                            {"MI101", "MI102", "MI103", "MI104", "MI105", "MI106", "MI107", "MI108", "MI109", "None"}                           
                           };

string labcourses[5][10] = {{"CH110", "CS110", "DA212", "DA261", "DA351","DA361", "DA451", "DA461", "DA651", "None"}, 
                            {"ME110", "PH110", "DA241", "DA262", "DA352","DA362", "DA452", "DA462", "DA551", "None"},
                            {"CE110", "EE102", "DA242", "DA263", "DA353","DA363", "DA453", "DA463", "DA661", "None"},
                            {"SA110", "SA110", "DA211", "DA264", "DA354","DA364", "DA454", "DA464", "DA561", "None"},
                            {"MI110", "MI110", "DA251", "DA265", "DA355","DA365", "DA455", "DA465", "DA671", "None"}                                                      
                           };
                        
// Function containing the algorithm for the student to shoose courses
void choose_courses()
 {
   cout<<"Enter the number adjacent to the course number to get enrolled int it"<<endl;
   cout<<endl;
   if(n>0)
   {
        for(int i=0;i<7;i++)
        {
            cout<<"Enter theory course for slot "<<tc[i]<<endl;
            int tselected;
            for(int j=0;j<10;j++)
            {
                cout<<j<<" : "<< theorycourses[i][j]<<endl;
            }
            cin>>tselected;
            if(tselected==9)
            {
                continue;
            }
            else if(tselected>=0 && tselected<9 && n>0)
            {
                n--;
                tt[tc[i]] = theorycourses[i][tselected];
            }
            else
            {
                cout<<"Either you exceeded the theory courses limit or you have entered wrong number"<<endl;
            }
            if(n==0)
            {
                break;
            }
            cout<<endl;   
        }
    }
   cout<<endl;
    if(l>0)
    {
        for(int i=0;i<5;i++)
        {
            cout<<"Enter lab course for slot "<<tc[i]<<endl;
            int lselected;
            for(int j=0;j<10;j++)
            {
            cout<<j<<" : "<< labcourses[i][j]<<endl;
            }
            cin>>lselected;
            if(lselected==9)
            {
                continue;
            }
            else if(lselected>=0 && lselected<9 && l>0)
            {
                l--;
                tt[lc[i]] = labcourses[i][lselected];
            }
            else
            {
                cout<<"Either you exceeded the lab courses limit or you have entered wrong number"<<endl;
            }
            if(l==0)
            {
                break;
            }           
            cout<<endl;
        }
    }
    cout<<endl;
    if(m>0)
    {
       cout<<"Chosse the tutorials you want by writing the numbers adjacent to it"<<endl;
        for(int i=0;i<7;i++)
        {
            cout<<i<<" : "<<tt[tc[i]]<<endl;
        }
        int tut_selected;
        for(int i=0;i<m;i++)
        {
            cin>>tut_selected;
            tt[tutc[tut_selected]] = tt[tc[tut_selected]];
        }
    }
    tt["LB"] = "Break";
 }
// This function alotts Professors to each course such that no Professor has to teach two courses having the same time slot.
void prof_allotment()
 {
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<9;j++)
        {
            prof.insert(pair<string, string>(theorycourses[i][j], "Prof" + to_string(i+j)));
        }
    }
    prof.insert(pair<string, string>("None", "None"));
 }

//This function displays the time table
void display_courses()
{
    ofstream file;
    file.open("Time_Table.txt");
    int time = 8;
    string days[5] = {"Mon", "Tue", "Wed", "Thu", "Fri"};
    file<<"\t\t\t";
    

    for(int j=0;j<8;j++)
    {
        if(time==8)
        {
            file<<"0"<<time<<":00"<<" - "<<"0"<<time+1<<":00"<<"\t|";
            time++;
        }
        if(time==9)
        {
            file<<"0"<<time<<":00"<<" - "<<time+1<<":00"<<"\t|";
            time++;
        }
        else{
            file<<time<<":00"<<" - "<<time+1<<":00"<<"\t|";
            time++;
        }
    }
    file<<endl;
    for(int i=0;i<5;i++)
    {
        file<<days[i]<<"\t\t\t\t";
        for(int j=0;j<9;j++)
        {
            file<<tt[slots[i][j]]<<"\t\t|\t";
        }       
        file<<endl;
    }
    file<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    file<<"Professors for each chosen course"<<endl;
    for(int i=0;i<7;i++)
    {
        file<<tt[tc[i]]<<" : "<<prof[tt[tc[i]]]<<endl;
    }
    file<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    file<<"Points to note :"<<endl;
    file<<"1) 8:00 - 9:00 slot is for tutorials"<<endl;
    file<<"2) SA : Sports Activity Course, MI: Minor Course"<<endl;
    file.close();
}

int main()
{
    cout<<"Enter number of theory courses(<8), lab courses(<6) and  tutorials(<6)"<<endl;
    cin>>n>>l>>m;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            tt.insert(pair<string, string> (slots[i][j], "None"));
        }
    }
    choose_courses();
    prof_allotment();
    display_courses();
}