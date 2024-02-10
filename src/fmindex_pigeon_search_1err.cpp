#include <sstream>

#include <seqan3/alphabet/nucleotide/dna5.hpp>
#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/fm_index/fm_index.hpp>
#include <seqan3/search/search.hpp>

using namespace std;
class Node {
public:	
	std::vector<seqan3::dna5>::const_iterator from;
	std::vector<seqan3::dna5>::const_iterator to;
	//std::vector<seqan3::dna5> string2;
	int errors;
	int leftorright;
	int level;
	Node * parent;
	int fromint;
	int toint;
	int fromintparent;
	int tointparent;
	//Node () {};
	Node () {};

	Node(std::vector<seqan3::dna5>::const_iterator from1, std::vector<seqan3::dna5>::const_iterator to1, int errors1, int leftorright1, Node  * parent1, int level1 ) {
		from1=from;
		to1=to;
		leftorright1=leftorright;
		parent1= parent;
		level1=level;
		
	}
    const std::vector<seqan3::dna5>::const_iterator  getfrom( ) const
	    {
        return from;
    }
    const int getfromint() const{
	//int fromint2=fromint;
	return fromint;

    }

    const int getfromintparent() const {
	return fromintparent;
    }
	
    const int gettointparent() const {
	return fromintparent;
    }
    const int gettoint() const{
	//int toint2=toint;
	return toint;
    }
	
    //const int gettoint2() {
//	int num;
//	this->
  //  }
    const std::vector<seqan3::dna5>::const_iterator  getto( ) const
    {
        return to;
    }
	
   // const std::string getstring () const
   // {   
//	std::vector<char> q_char;
//	std::vector<seqan3::dna5> vec(this->getfrom(),this->getto());
//	int sz=vec.size();
//	for (int i=0; i<sz;i++){
		//(seqan3::dna5 value : std::vector<seqan3::dna5> (this->getfrom(),this->getto())) {
//		q_char.push_back(vec[i].to_char());
		//std::cout<<vec[i].to_char();
//	}
  // 	return std::string(q_char.begin(),q_char.end());

   // }
    //const std::string getstring2 () const
    //{   
//	std::vector<char> q_char;
//	std::vector<seqan3::dna5> vec = string2 ;
//	int sz=vec.size();
//	for (int i=0; i<sz;i++){
		//(seqan3::dna5 value : std::vector<seqan3::dna5> (this->getfrom(),this->getto())) {
//		q_char.push_back(vec[i].to_char());
		//std::cout<<vec[i].to_char();
//	}
  // 	return std::string(q_char.begin(),q_char.end());

   // }
    
    //const std::string getparentstring() const{
//	const Node a=*this->parent;
//	return a.getstring2();
		
  //  }


    Node * getnode() const{
	return parent;
    }

    const int & geterrors( ) const
    {
        return errors;
    }

    const int & getlevel( ) const
    {
        return level;
    }

    Node*  getparent( )
    {
        return this->parent;
    }


    
    //const std::string

};




//std::ostream& operator<<(std::ostream &out, Node const& node) {
  //  out << node.getstring() << ':';
    //out <<node.string<<':';
    //out << *node.getto() << ':';
    // and so on... 
   // return out;
//}
std::vector<Node> v;
void build_tree(const std::vector<seqan3::dna5> & query,int errors,  const std::vector<std::vector<seqan3::dna5>> & reference, std::vector<Node> & tree, int level, int leftorright,int start, int end, Node * parent) {
//	
//	
	//std::cout<<"length of tree:"<<tree.size();
	//std::cout<<"last elem"<<std::endl;
	//if(!tree.size()==0){
	//	Node lastNode=tree.back();
		//std::string c=lastNode.getstring();
		//std::cout<<c<<std::endl;
	//	std::string ci=lastNode.getstring2();
	//	std::cout<<ci;
	//}
	//if (tree.size()==0)
	//	std::vector<Node> tree12;
	//std::cout<<std::endl;
    	int plen=std::floor(double(query.size()/(errors+1)));
	auto size = query.size(); 
	int left=std::ceil(double(errors+1)/2);
	int lk=std::floor( double( left*(errors)/(errors+1)));
	int rk=std::floor(double( (errors+1)-left)*(errors)/(errors+1) );
	Node NodeA;
	//Node NodeA(query.begin(),query.end(),errors,leftorright,nullptr,level );
	NodeA.fromint=start;
	NodeA.toint=end;
	NodeA.from=query.begin();
	NodeA.to=query.end();
	//NodeA.string2=query;
        NodeA.errors=errors;
	NodeA.leftorright=leftorright; 
	NodeA.level=level;
	NodeA.parent=parent;
	
	//NodeA.fromintparent=(*NodeA.parent).fromint;
	//if (tree.size()!=0)
		//NodeA.parent=&(tree[0]);
	//std::cout<<"level: "<<NodeA.getlevel()<<std::endl;
	//std::cout<<"errors: "<<NodeA.geterrors();
	//std::cout<<"Query:";
	//stf::vector<std::dna5> vec(NodeA.from
	//for(int h=0;h<query.size();h++){
	//	std::cout<<query[h].to_char();
	//}
	//std::cout<<std::endl<<"query: ";
	//std::cout<<NodeA.getstring2();
	//std::cout<<std::endl;
	//std::cout<<"String from: " <<NodeA.getfromint();
	//std::cout<<"to: "<<NodeA.gettoint();
	//if (NodeA.parent != nullptr) {
	//	Node a =*NodeA.parent;
	//	NodeA.fromintparent=a.fromint;
	//	NodeA.tointparent=a.toint;
		//std::cout<<"parent to int"<<a.getto()-NodeA.getto();
		//std::cout<<"parent: "<<a.getstring2();
	//}
	//std::cout<<"level: "<<NodeA.getlevel()<<std::endl;
	//seqan3::dna5 charac=*NodeA.getfrom();
	//std::cout<<tree.back().parent->getstring2();
	tree.push_back(NodeA);
	if (errors==0) {	
		return;
	}

	build_tree(std::vector<seqan3::dna5> (query.begin(),query.begin()+left*plen),lk,  reference, tree,level+1,0,start,left*plen-1 , &tree.back());

	build_tree(std::vector<seqan3::dna5> (query.begin()+left*plen ,query.end()),rk,  reference,  tree, level+1,1,left*plen,end , & tree.back());
		

}


int main(int argc, char const* const* argv) {
    seqan3::argument_parser parser{"fmindex_pigeon_search", argc, argv, seqan3::update_notifications::off};

    parser.info.author = "SeqAn-Team";
    parser.info.version = "1.0.0";

    auto index_path = std::filesystem::path{};
    parser.add_option(index_path, '\0', "index", "path to the query file");

    auto reference_file = std::filesystem::path{};
    parser.add_option(reference_file, '\0', "reference", "path to the reference file");

    auto query_file = std::filesystem::path{};
    parser.add_option(query_file, '\0', "query", "path to the query file");

    auto number_of_queries = size_t{100};
    parser.add_option(number_of_queries, '\0', "query_ct", "number of query, if not enough queries, these will be duplicated");

    auto number_of_errors = uint8_t{0};
    parser.add_option(number_of_errors, '\0', "errors", "number of allowed hamming distance errors");

    try {
         parser.parse();
    } catch (seqan3::argument_parser_error const& ext) {
        seqan3::debug_stream << "Parsing error. " << ext.what() << "\n";
        return EXIT_FAILURE;
    }

    // loading our files
    auto reference_stream = seqan3::sequence_file_input{reference_file};
    auto query_stream     = seqan3::sequence_file_input{query_file};

    // read reference into memory
    std::vector<std::vector<seqan3::dna5>> reference;
    for (auto& record : reference_stream) {
        reference.push_back(record.sequence());
    }

    // read query into memory
    std::vector<std::vector<seqan3::dna5>> queries;
    for (auto& record : query_stream) {
        queries.push_back(record.sequence());
    }

    // loading fm-index into memory
    using Index = decltype(seqan3::fm_index{std::vector<std::vector<seqan3::dna5>>{}}); // Some hack
    Index index; // construct fm-index
    {
        seqan3::debug_stream << "Loading 2FM-Index ... " << std::flush;
        std::ifstream is{index_path, std::ios::binary};
        cereal::BinaryInputArchive iarchive{is};
        iarchive(index);
        seqan3::debug_stream << "done\n";
    }

    // duplicate input until its large enough
    while (queries.size() < number_of_queries) {
        auto old_count = queries.size();
        queries.resize(2 * old_count);
        std::copy_n(queries.begin(), old_count, queries.begin() + old_count);
    }
    queries.resize(number_of_queries); // will reduce the amount of searches

    seqan3::configuration const cfg = seqan3::search_cfg::max_error_total{seqan3::search_cfg::error_count{0}};

    using namespace std::chrono;
    //auto start = high_resolution_clock::now();
    int l=0;
    std::vector<Node> tree;
    tree.reserve(30);
    build_tree(queries[1],1,reference,tree,0,0,0,queries[1].size(),nullptr);
    std::cout<<"hello";
    auto start = high_resolution_clock::now();
    for (auto & query : queries) {
	//if(0==0)
	//	break;
	//std::vector<Node> tree;
	//tree.reserve(10);
	//build_tree(query,2,  reference, tree, 0, 0,0,query.size(),nullptr);
	//std::cout<<"original query: ";	
	//for(int ll=0;ll<query.size();ll++)
	//	std::cout<<query[ll].to_char();
	//std::cout<<std::endl;
	
	std::vector<int> foundpositions;
	int kkk=0;
	bool alreadyfound=false;
	for (int iii=0; iii<tree.size();iii++){
		Node A=tree[iii];
		if(alreadyfound)
			break;
		if (A.geterrors()==0){
			//std::cout<<"leaf: "<<kkk;
			//std::cout<<"subquery matched"<<std::endl<<A.getstring2()<<std::endl;
			//if (A.getparent()==nullptr);
				//std::cout<<"problem";
			//std::cout<<A.getparentstring();
			//std::cout<<aa.getstring2();
			//std::vector<seqan3::dna5> test=aa.string2;
			//std::cout<<test[0].to_char();
			std::vector<seqan3::dna5> vec=std::vector<seqan3::dna5>(query.begin()+A.getfromint(),query.begin()+A.gettoint());
			
			//remove from list when already found
			auto results=seqan3::search(vec,index); //search result for 0 errors with fm-index
			int starti=0;
			int endi=0;
			//while(A.geterrors()<2) {
			for (auto result : results) {
			int whilloop =0;
				while(A.geterrors()<1) {
					//std::cout<<"iteration:"<< whilloop<<std::endl;
					int errorcounter=0;
					int startcounterref=0;
					int startcounterref2=0;
					#include <algorithm>
				//dont test if already found:
					int testedpos=result.reference_begin_position();
					//std::cout<<"testedpos: "<<testedpos;
					Node& aa=*A.parent;
				//std::cout<<"now verify .. try to match"<<std::endl;
					if (A.leftorright==0){  //left subtree
						//for (int i=0; i<(A.tointparent-A.fromintparent);i++)
							//std::cout<<query[A.fromintparent+i].to_char();
						//std::cout<<std::endl;
						starti=A.gettoint();
						startcounterref=0;
						startcounterref2=A.toint-A.fromint;
						//	Node aa =*A.parent;
						endi = aa.toint;
						//std::cout<<"left tree";
						testedpos=testedpos+0;
					}
					if (A.leftorright==1) { //rightsubtree
						//for (int i=0;i<(A.tointparent-A.fromintparent);i++)
							//std::cout<<query[A.fromintparent+i].to_char();
						startcounterref=(aa.fromint-A.fromint);
						//std::cout<<startcounterref;
						//std::cout<<std::endl;	
						starti=aa.fromint;
						endi= A.fromint;
						//std::cout<<"right tree";
						testedpos=testedpos-starti;
					}
					std::vector<int>::iterator position = std::find(foundpositions.begin(), foundpositions.end(), testedpos);
					
					if (position != foundpositions.end()&&A.getlevel()==0) {
				    		// == myVector.end() means the element was not found
						std::cout<<"dont test again";
						break;
					}
					//std::vector<seqan3::dna5> llll = std::vector<seqan3::dna5> (reference.begin()+53602670,reference.begin()+53602670);
					//std::cout<<"size"<<llll.size();
					//std::cout<<std::endl;
					//std::cout<<"against position: "<<result.reference_begin_position()<<" with sequence: "<<std::endl;
					//for (int i=0;i<(A.tointparent-A.fromintparent);i++)
						//std::cout<<reference[0][result.reference_begin_position()+i+startcounterref].to_char();
					//std::cout<<"by only checking the subpattern: "<<std::endl;
					//for (int i=0; i<(endi-starti); i++)
					//	std::cout<<reference[0][result.reference_begin_position()+i+startcounterref+startcounterref2].to_char();
					//std::cout<<std::endl;
					for (int i=0; i<(endi-starti);i++) {
						//std::cout<<query[starti+i].to_char();
						if (reference[0][result.reference_begin_position()+i+startcounterref+startcounterref2].to_char() !=query[starti+i].to_char()){
							//std::cout<<"error";
							errorcounter+=1;
						}
						if (errorcounter>A.geterrors()+1) { //adapt when more than 1 additional level
							//std::cout<<"->discarded!"<<std::endl;
							break;
						}
						if (i==((endi-starti)-1)&&aa.getlevel()==0) {
							//std::cout<<"level: "<<A.getlevel();
							//std::cout<<"starti: "<<starti<<std::endl;
							//std::cout<<"->match approved!"<<std::endl;
							foundpositions.push_back(int(testedpos));
							alreadyfound=1;
							//goto stop;
						}
						;
					}
				
				A=*A.parent;
				whilloop+=1;
				} //end while
			//if(&A==nullptr){
			//	break;
			//}
			}//end for result in results
		kkk+=1;
		}//end if errors =0
	
	}//end for loop over tree size
	
	//goto:
	//std::cout<<"";
	l++;
	
	//std::cout<<"finalhits:";
	for (int i=0;i<foundpositions.size();i++) {
		std::cout<<foundpositions[i]<<std::endl;
	}


	}//end for loop queries	
    auto stop = high_resolution_clock::now();
    duration <double, std::milli> ms_double=stop-start;
    //auto duration=duration_cast<microseconds>(stop-start);
    std::cout<<"Running time for "<<queries.size()<<" many queries of length 100:"<<ms_double.count()<<"milliseconds"<<std::endl;

    //!TODO !ImplementMe use the seqan3::search to fin:d a partial error free hit, verify the rest inside the text
    // Pseudo code (might be wrong):
    // for query in queries:
    //      parts[3] = cut_query(3, query);
    //      for p in {0, 1, 2}:
    //          for (pos in search(index, part[p]):
    //              if (verify(ref, query, pos +- ....something)):
    //                  std::cout << "found something\n"

    return 0;
}
