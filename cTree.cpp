/* cTree.cpp описана реализаци€ команд дл€ управлени€ в.ф.с. 
*/
#include "cTree.h"
//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

//typedef fTree<Catalog> tTree; 
//tTree Root;
//tTree *node_f;


using namespace std;
//функци€ удал€ет из строки указанную строку(по умолчанию пробел), при этом измен€етс€ вход€ший аргумент
std::string trim(std::string& s,const std::string& drop = " ")
{
 std::string r=s.erase(s.find_last_not_of(drop)+1);
 return r.erase(0,r.find_first_not_of(drop));
}
std::string trim_n(std::string s,const std::string& drop = "\n")
{
 std::string r=s.erase(s.find_last_not_of(drop)+1);
 return r.erase(0,r.find_first_not_of(drop));
}
bool MyDataSortPredicate(const tTree& d1, const tTree& d2)
{
	return d1.item.name_f < d2.item.name_f;
}
std::string deleteALL(tTree &folder_f)
{
	std::string treturn="OK";
	for(tVECTREE::iterator nodeDel = folder_f.children.begin();nodeDel!=folder_f.children.end();
						nodeDel++)
	 {
		 if(nodeDel->item.locks.size()>0){treturn= "error: file " +nodeDel->item.name_f+ " locked";  break;}
		 else
			 if(nodeDel->item.type_f==FOLDER_T){
				 if( deleteALL(*nodeDel)=="OK")
				   {treturn= "OK";}
			 }else {treturn ="OK";}
		  
	}
    return treturn;

}
void printTree( tTree node,int levelPrint,std::string str, std::string &res)
{  
	std::string tmp="";
	
    std::cout <<str<<node.item.name_f<<endl;
	 res+='\n'+str+node.item.name_f;	
//	else res+=str+node.item.name_f;	
	if( node.item.locks.size()>0){
		for (tLOCK::iterator os =node.item.locks.begin();
								   os!=node.item.locks.end(); 
								   os++) {
									   tmp+= " by "+*os;
		
		}


	res+="[LOCKED"+ tmp + "]";
	}
	str.append("|_");
	//if(levelPrint==0){std::cout <<node.item.name_f<<endl;}
//	else
//	{
	    
		/*	std::vector<fTree*>::iterator i;
			for(i = node.children.begin(); i != node.children.end(); ++i)
			{	
				tmp=str;
				tmp.append( node.item.name_f);
			}
		*/
		for(unsigned int i =0; i<node.children.size();i++){
		//std::cout<<node.children[i]->item.name_f;
			
			printTree(node.children[i],levelPrint,str,res);
		}
//=============================================================
//	}
	
//	std::cout <<node.item.name_f<<endl;
    
}
tTree * commandCD(tTree &Root,tTree &folder_f, std::string Path)
{  
 bool fRoot=false;
// Path.erase(Path.find_last_not_of("\n")+1);

 if (trim_n(Path).compare("/")==0){
    return &Root;

	}else
	 {  
	
	std::string tstr;
	int pos=-1;
	
		 std::string fstr;
		 tstr=Path;
		 if (tstr.substr(0,1).compare("/")==0){
			 tstr=tstr.substr(1,tstr.length()-1);
		     fRoot=true;
		    }
		 pos=tstr.find_first_of("/");
		 if (pos>0){		  
			 bool flag = false;
			 fstr=tstr.substr(0,pos);
			 Path=tstr.substr(pos,tstr.length()-1);
             for(unsigned int i =0; i<Root.children.size();i++){
		         
				 if(trim_n(Root.children[i].item.name_f).compare(trim_n(fstr))==0){
					 flag=!flag; return commandCD(Root.children[i],Root.children[i],  Path);
					 

				    }
                   }    
		       
		       if (!flag)return NULL;
	        }
		   else{
			   bool flag = false;
			   fstr=tstr.substr(0,tstr.length());
			   if (!fRoot )
	           for(unsigned int i =0; i<folder_f.children.size();i++){	         
				 if(trim_n(folder_f.children[i].item.name_f).compare(trim_n(fstr))==0){
					 flag=!flag;return  &folder_f.children[i];break;
				  }		 
                } else
					for(unsigned int i =0; i<Root.children.size();i++){	         
					 if(trim_n(Root.children[i].item.name_f).compare(trim_n(fstr))==0){
						 flag=!flag;return  &Root.children[i];break;
					  }		 
               }

		       
		       if (flag==false)return NULL;
	
		      }

	}
 
}
bool commandMD(tTree &Root,tTree &folder_f, std::string Path,std::string &res, char type_d){
 tTree folder;
 if (trim_n(Path).compare("/")==0){
    return NULL;
	 
	}else
	 {  
	
	std::string tstr;
	int pos;
	
		 std::string fstr;
		 tstr=Path;
		 if (tstr.substr(0,1).compare("/")==0)
			tstr=tstr.substr(1,tstr.length()-1);
		 pos=tstr.find_first_of("/");
		 if (pos>0){		  
			 bool flag = false;
			 fstr=tstr.substr(0,pos);
			 Path=tstr.substr(pos,tstr.length()-1);
             for(unsigned int i =0; i<Root.children.size();i++){
		         
				 if(Root.children[i].item.name_f.compare(fstr)==0){
					 flag=!flag; commandMD(Root.children[i],Root.children[i],  Path, res,type_d);
				    }
                   }    
		       
			 if (!flag){
				 res= "wrong path";
				 return NULL;
			 }
	        }
		   else{
			   
			    fstr=tstr.substr(0,tstr.length());
   				
    			folder.item.name_f=trim_n(trim(fstr));
				folder.item.type_f=type_d;

				folder_f.children.push_back(folder);
				
               std::sort(folder_f.children.begin(), folder_f.children.end(),MyDataSortPredicate);
 /*				for(int i = 0;i<folder.children.size();i++)
					 {  //tTree new_it=os;
						 if(i<folder.children.size()-1)
						 {  
							
							
							 if(!MyDataSortPredicate(folder.children[i],folder.children[i+1])){
								 tTree temp_it =folder.children[i];
								 folder.children[i]=folder.children[i+1];
								 folder.children[i+1]=temp_it;
							  
							 }
						 }
				            
				 }*/
                res= "created a folder " +fstr ;
			   /*for(int i =0; i<folder_f.children.size();i++){	         
				 if(folder_f.children[i].item.name_f.compare(fstr)==0){
					 flag=!flag;return  &folder_f.children[i];
				  }*/
               }    
		       
		      // if (flag==false)return NULL;
	
		      }

	



}
/*int _tmain(int argc, _TCHAR* argv[])
{  
    node_f=&Root;
	Root.item.name_f="/";
	std::string test,tstr;
		std::cout<< "Testing"<<endl;
		while(1){
			test.clear();
			//cin.getline(test.c_str, 255);
			getline(cin, test); 
         std::transform(test.begin(), test.end(), test.begin(), tolower );
		 if(test.compare("print")==0) {
		  
		   printTree(Root,0,"");
		 }
		 else
		 if (test.compare("quit")==0) break;
		 else{

			 tstr=test;
			 if(tstr.substr(0,2).compare("md")==0){
				 				
			    tstr=tstr.substr(2,tstr.length()-2);
		    	

				 commandMD(Root,*node_f,trim(tstr));
				
			 }
                else 
				if(tstr.substr(0,2).compare("cd")==0){
				  tstr=tstr.substr(2,tstr.length()-2);
				  tstr= trim(tstr);
				  tTree *nodeT=commandCD(Root,*node_f,tstr);
				  if( nodeT!=NULL)
					  node_f= nodeT;
			   }


		 }
	     
		
		}
	//delete(Root);
	return 0;
}*/
int commandRD(tTree &Root,tTree &folder_f, std::string Path,std::string &res)
{

 bool fRoot=false;
 if (trim_n(Path).compare("/")==0){
   
	 res="!err";
	}else
	{//1  
	
	std::string tstr;
	int pos=-1;
	
		 std::string fstr;
		 tstr=Path;
	  if (tstr.substr(0,1).compare("/")==0){//2
			 tstr=tstr.substr(1,tstr.length()-1);
		     fRoot=true;
		    }//2
		 pos=tstr.find_first_of("/");
		 if (pos>0){//3		  
			 bool flag = false;
			 fstr=tstr.substr(0,pos);
			 Path=tstr.substr(pos,tstr.length()-1);
             for(unsigned int i =0; i<Root.children.size();i++){//4
		          if(trim_n(Root.children[i].item.name_f).compare(trim_n(fstr))==0)
				 {//5
					 flag=!flag; commandRD(Root.children[i],Root.children[i],  Path,res);
				    }//5
                   } //4   
		       
		       if (!flag)res="!err";
	        }//3
		   else{//6
			   bool flag = false;
			   fstr=tstr.substr(0,tstr.length());
			   fstr=trim_n(fstr);
			   if (!fRoot ){

			     bool folder_lock ;
   			 	for(tVECTREE::iterator nodeDel = folder_f.children.begin();nodeDel!=folder_f.children.end();
					nodeDel++)
				{//7	
					
				 if(trim_n(nodeDel->item.name_f).compare(trim_n(fstr))==0){//8
		            folder_lock=false;
					flag=!flag;
					tTree *nodeT = &(*nodeDel);
					 for(tVECTREE::iterator os =nodeT->children.begin();
							   os!=nodeT->children.end(); 
							   os++)
					 {if(os->item.locks.size()>0){folder_lock=true;break;}
					  if(os->item.type_f==FOLDER_T){folder_lock=true;break;}
					 }   
					 /*if((os->item.locks.size()>0)||(os->item.type_f==FOLDER_T)){
							   folder_lock=true;
							   res= "!err error command RD";
							   return 0;
							   break;
						   }*/
						
						  if (folder_lock)  res= "error command RD";
						  else
							  if (nodeDel->item.type_f==FOLDER_T){
								  folder_f.children.erase(nodeDel);
								  res= "OK";
								  return 1;
								 }
							  else{ 
									res=" it's not folder";
									return 0;
							  }
							break;
					      
			    	 }//8
			    }//7
			  }
			   else
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			   {  bool folder_lock ;
   			 	for(tVECTREE::iterator nodeDel = Root.children.begin();nodeDel!=Root.children.end();
					nodeDel++)
				{//7	
					
				 if(trim_n(nodeDel->item.name_f).compare(trim_n(fstr))==0){//8
		            folder_lock=false;
					flag=!flag;
					tTree *nodeT = &(*nodeDel);
					 for(tVECTREE::iterator os =nodeT->children.begin();
							   os!=nodeT->children.end(); 
							   os++)
					 {if(os->item.locks.size()>0){folder_lock=true;break;}
					  if(os->item.type_f==FOLDER_T){folder_lock=true;break;}
					 }   
					 /*if((os->item.locks.size()>0)||(os->item.type_f==FOLDER_T)){
							   folder_lock=true;
							   res= "!err error command RD";
							   return 0;
							   break;
						   }*/
						
						  if (folder_lock)  res= "!err error command RD";
						  else
							  if (nodeDel->item.type_f==FOLDER_T){
								  Root.children.erase(nodeDel);
								  res= "OK";
								  return 1;
								 }
							  else{ 
									res=" it's not folder";
									return 0;
							  }
							break;
					      
			    	 }//8
			    }//7
			  }

		       
		       if (flag==false) res="!err The folder not found";
	
		      }//6

	}//1

return 0;
}
void commandDELTREE(tTree &Root,tTree &folder_f, std::string Path,std::string &res)
{

 bool fRoot=false;
 if (Path.compare("/\n")==0){
   
	 res="!err";
	}else
	 {  
	
	std::string tstr;
	int pos=-1;
	
		 std::string fstr;
		 tstr=Path;
		 if (tstr.substr(0,1).compare("/")==0){
			 tstr=tstr.substr(1,tstr.length()-1);
		     fRoot=true;
		    }
		 pos=tstr.find_first_of("/");
		 if (pos>0){		  
			 bool flag = false;
			 fstr=tstr.substr(0,pos);
			 Path=tstr.substr(pos,tstr.length()-1);
             for(unsigned int i =0; i<Root.children.size();i++){
		         
				 if(Root.children[i].item.name_f.compare(fstr)==0){
					 flag=!flag; commandDELTREE(Root.children[i],Root.children[i],  Path,res);
				    }
                   }    
		       
		       if (!flag)res="!err";
	        }
		   else{//6
			   bool flag = false;
			   fstr=tstr.substr(0,tstr.length());
			   fstr=trim_n(fstr);
			   if (!fRoot ){

			     bool folder_lock ;
   			 	for(tVECTREE::iterator nodeDel = folder_f.children.begin();nodeDel!=folder_f.children.end();
					nodeDel++)
				{//7	
					
				 if(trim_n(nodeDel->item.name_f).compare(trim_n(fstr))==0){//8
		            folder_lock=false;
					std::string ts;
					flag=!flag;
					tTree *nodeT = &(*nodeDel);
					/*for(tVECTREE::iterator os =nodeT->children.begin();
							   os!=nodeT->children.end(); 
							   os++)
					 {if(os->item.locks.size()>0){folder_lock=true;break;}

					 }*/   

						
							  if (nodeDel->item.type_f==FOLDER_T)
							  {
	    						   ts= deleteALL(*nodeDel);
		    					  if(ts=="OK")
			    					  { folder_f.children.erase(nodeDel); res= "OK";}
								  else
									  {res=ts;break;}		  
								 
								 }
							  else{ 
									res=" it's not folder";
									
							  }
							break;
					      
				 }//8
			    }//7
			  }
			   else
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			   {  bool folder_lock ;
   			 	for(tVECTREE::iterator nodeDel = Root.children.begin();nodeDel!=Root.children.end();
					nodeDel++)
				{//7	
					
				 if(trim_n(nodeDel->item.name_f).compare(trim_n(fstr))==0){//8
		            folder_lock=false;
					std::string ts;
					flag=!flag;
					tTree *nodeT = &(*nodeDel);
					 for(tVECTREE::iterator os =nodeT->children.begin();
							   os!=nodeT->children.end(); 
							   os++)
					 {if(os->item.locks.size()>0){folder_lock=true;break;}
					 
					 }   
					 /*if((os->item.locks.size()>0)||(os->item.type_f==FOLDER_T)){
							   folder_lock=true;
							   res= "!err error command RD";
							   return 0;
							   break;
						   }*/
						
							  if (nodeDel->item.type_f==FOLDER_T)
							  {
	    						  ts= deleteALL(*nodeDel);
		    					  if(ts=="OK")
			    					  { Root.children.erase(nodeDel); res= "OK";}
								  else
									  {res=ts;break;}		  
								 
								 }
							  else{ 
									res=" it's not folder";
									
							  }
							break;
					      
			    	 }//8
			    }//7
			  }

		       
		       if (flag==false) res="!err The folder not found";
	
		      }//6


	}


}
void commandDEL(tTree &Root,tTree &folder_f, std::string Path,std::string &res)
{

 bool fRoot=false;
 if (trim_n(Path).compare("/")==0){
   
	 res="!err";
	}else
	 {  
	
	std::string tstr;
	int pos=-1;
	
		 std::string fstr;
		 tstr=Path;
		 if (tstr.substr(0,1).compare("/")==0){
			 tstr=tstr.substr(1,tstr.length()-1);
		     fRoot=true;
		    }
		 pos=tstr.find_first_of("/");
		 if (pos>0){		  
			 bool flag = false;
			 fstr=tstr.substr(0,pos);
			 Path=tstr.substr(pos,tstr.length()-1);
             for(unsigned int i =0; i<Root.children.size();i++){
		         
				 if(trim_n(Root.children[i].item.name_f).compare(trim_n(fstr))==0){
					 flag=!flag; commandDEL(Root.children[i],Root.children[i],  Path,res);
				    }
                   }    
		       
		       if (!flag)res="!err";
	        }
		   else{
			   bool flag = false;
			   fstr=tstr.substr(0,tstr.length());
			   fstr=trim_n(fstr);
			   if (!fRoot )

			   
   			 	for(tVECTREE::iterator nodeDel = folder_f.children.begin();nodeDel!=folder_f.children.end();
					nodeDel++)
				{	
					
				  if(trim_n(nodeDel->item.name_f).compare(fstr)==0){
//удаление		        
					tTree *nodeT = &(*nodeDel);
					

						
							flag=!flag;
							if (nodeDel->item.type_f==FILE_T){
								if(nodeDel->item.locks.size()==0){
									folder_f.children.erase(nodeDel);break;
																	}
								else { res=" file is locked"; break; }
							  }
							else {res=" it's not file"; break;}
				  }

				}		 
			   else
					
						for(tVECTREE::iterator nodeDel = Root.children.begin();nodeDel!=Root.children.end();
							nodeDel++)
						{	
							
					     if(trim_n(nodeDel->item.name_f).compare(fstr)==0){
//удаление		        
							tTree *nodeT = &(*nodeDel);
															
							flag=!flag; 
							if (nodeDel->item.type_f==FILE_T){//1
								if(nodeDel->item.locks.size()==0){
									Root.children.erase(nodeDel);break;
																}
								else {res=" file is locked"; break;}
							     }//1
							else {res=" it's not file"; break;}
						 }
					  }		 
               
		       
		       if (flag==false) res="!err The folder not found";
	
		      }

	}


}
int commandCOPY(tTree &Root,tTree &folder_f, std::string Path,std::string &res){

	std::string path_out,path_in ;
	path_out= Path.substr(0, Path.find_first_of(" ")); 
	path_in= Path.substr(Path.find_last_of(" ")+1,Path.length()-Path.find_last_of(" ")-1); 
	if((path_in!="")&&(path_out!=""))
	{  
		trim(path_in);
		trim(path_out);
		tTree *node_out,*node_in;
		node_out=commandCD(Root,folder_f,path_out);
		node_in= commandCD(Root,folder_f,path_in);
		if((node_in!=NULL)&&(node_out!=NULL)){
			tTree *nodeT=commandCD(Root,folder_f,path_in.append("/"+path_out));
				if( nodeT==NULL) {
			      if(node_in->item.type_f==FOLDER_T){node_in->children.push_back(*node_out);		
				  res= "copied successfully";
				  return 1;
				  }
				  else{
                  res="such name already is";		 
				  return 0;
				  }
				}
		}else
		{
           res="wrong path";		 
		   return 0;
		}
	 }
}

//функци€ исполнени€ комманд посланиных пользователем
std::string command(std::string test,tTree &Root, tTree **node_f,std::string user_name)
{
	std::string tstr,res ="";
	std::transform(test.begin(), test.end(), test.begin(), tolower );
	trim(test);
		// if(test.compare("print")==0) 
	if(test.substr(0,5)=="print") {
		  
		   printTree(Root,0,"",res);
		   return res;
		 }
		 else
		{

			 tstr=test;
			 if(tstr.substr(0,2).compare("md")==0){
								
			    tstr=tstr.substr(2,tstr.length()-2);
				tTree *nodeT=commandCD(Root,**node_f,trim(tstr));
				if( nodeT==NULL) {
					commandMD(Root,**node_f,trim(tstr),res,FOLDER_T);
				 return res;}
				 else
                 return res="a folder name  already is";
			 }
                else 
			 if(tstr.substr(0,2).compare("mf")==0){
								
			    tstr=tstr.substr(2,tstr.length()-2);
				tTree *nodeT=commandCD(Root,**node_f,trim(tstr));
				if( nodeT==NULL) {
					commandMD(Root,**node_f,trim(tstr),res,FILE_T);
				 return res;}
				 else
                 return res="folder with that name already exists";
			 }
                else 

				if(tstr.substr(0,2).compare("cd")==0){
				  tstr=tstr.substr(2,tstr.length()-2);
				  tstr= trim(tstr);
				  tTree *nodeT=commandCD(Root,**node_f,tstr);
				  if( nodeT!=NULL){
					  if(nodeT->item.type_f==FOLDER_T){
					   *node_f= nodeT;
					   return res="ok";
					  }
					  else return res="it's not folder";
				    }else
						return res="wrong path";

				}
				else
				 if(tstr.substr(0,4).compare("lock")==0){
				  tTree *lock;
				  tstr=tstr.substr(4,tstr.length()-4);
				  tstr= trim(tstr);
				  tTree *nodeT=commandCD(Root,**node_f,tstr);
				  if( nodeT!=NULL){
					  if(nodeT->item.type_f=FILE_T){
						 lock = nodeT;
						 lock->item.locks.push_back(user_name);return res="OK";}else  return res="it's not file";
					 }
				 }
				 else
					 if(tstr.substr(0,6).compare("unlock")==0){
				  tTree *lock;
				  tstr=tstr.substr(6,tstr.length()-6);
				  tstr= trim(tstr);
				  tTree *nodeT=commandCD(Root,**node_f,tstr);
				  if( nodeT!=NULL)
					  if(nodeT->item.type_f==FILE_T){
					 lock = nodeT;
					// lock->item.locks.push_back(user_name);
					 for (tLOCK::iterator os =lock->item.locks.begin();
								   os!=lock->item.locks.end(); 
								   os++){
					    if(*os==user_name){lock->item.locks.erase(os);return res="OK";break;}	 
					 }
				   }
					  else  return res="it's not file";
					 }
				else
			     if(tstr.substr(0,2).compare("rd")==0){
				  tstr=tstr.substr(2,tstr.length()-2);
				  tstr= trim(tstr);
                   commandRD(Root,**node_f, tstr,res);
				  /* tTree *nodeT=commandCD(Root,**node_f,tstr);
				  if( nodeT!=NULL)
				    {}
				  else return "!err";*/
					 
				 }
	
              else
			     if(tstr.substr(0,7).compare("deltree")==0){
				  tstr=tstr.substr(7,tstr.length()-7);
				  tstr= trim(tstr);
                   commandDELTREE(Root,**node_f, tstr,res);
	
				return res;
					 
				 }
              else
			     if(tstr.substr(0,3).compare("del")==0){
				  tstr=tstr.substr(3,tstr.length()-3);
				  tstr= trim(tstr);
                   commandDEL(Root,**node_f, tstr,res);
				  /* tTree *nodeT=commandCD(Root,**node_f,tstr);
				  if( nodeT!=NULL)
				    {}
				  else return "!err";*/
					 
				 }

              else
			     if(tstr.substr(0,4).compare("copy")==0){
				  tstr=tstr.substr(4,tstr.length()-4);
				 // tstr= trim(tstr);
				  for(;;)
					  if(tstr[0]==' ')
				         tstr.erase(0,1);
					  else break;

                   commandCOPY(Root,**node_f, tstr,res);
					return res;
					 
				 }
			 else
			     if(tstr.substr(0,4).compare("move")==0){
				  tstr=tstr.substr(4,tstr.length()-4);
				 // tstr= trim(tstr);
				  for(;;)
					  if(tstr[0]==' ')
				         tstr.erase(0,1);
					  else break;

                  if( commandCOPY(Root,**node_f, tstr,res))
					  tstr=tstr.substr(0,tstr.find_first_of(" "));
				      trim(tstr);
					  commandDELTREE(Root,**node_f, tstr,res);
					  return res;

					 
			   
				 }
				 else 
					 return res="unknown command";



		 }
 return res;
}
