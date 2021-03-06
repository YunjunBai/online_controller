/*
 * TransitionFunction.hh
 *
 * 
 */

/** @file **/

#ifndef TRANSITIONFUNKTION_HH_
#define TRANSITIONFUNKTION_HH_

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdint>
#include <memory>

/* to get abs_type alias */
#include <UniformGrid.hh>
#include <WinningDomain.hh>


/** @namespace scots **/ 
namespace scots {

/**
 * @brief abs_ptr_type defines type used to point to the array m_pre (default = uint64_t) \n
 * determinse implicitely an upper bound on the number of transitions (default = * 2^64-1)
 **/
using abs_ptr_type=std::uint64_t;

/**
 * @class TransitionFunction
 * 
 * @brief The transition function of the abstraction
 *
 * The transition function can either be read from file or 
 * constructed with the help of AbstractionGB.
 *  
 * The set of states is given \f$ S:=\{0,\ldots,N \}\f$ where N is stored in m_no_states
 * The set of inputs is given \f$ A:=\{0,\ldots,M \}\f$ where M is stored in m_no_inputs
 * 
 * A transition is a triple \f$ (i,j,k) \f$ where \f$i,k\in A\f$ and \f$j\in A\f$
 * - the element \f$i\f$ is referred to as pre
 * - the element \f$k\f$ is referred to as post
 * - the element \f$j\f$ is referred to as input
 * 
 * The data structure is particularly tailored to be used in the 
 * minimal and maximal fixed point computations, in which the list of pres i
 * associated with a post k and input j need to be accessed fast:\n
 * the pres itself are stored in the array m_pre\n
 * the position of the pres in m_pre is stored in the array m_pre_ptr\n
 * the number of pres is stored in  m_no_pre
 * 
 * To copy the pres of the state-input pair (k,j) to a std::vector<abs_type> pre the
 * following code is implemented in get_pre(k,j)
  \verbatim
  for(abs_type i=0; i<m_no_pre[k*M+j]; i++) {
    pre.push_back(m_pre[m_pre_ptr[k*M+j]]+i);
  }
  \endverbatim
 * 
 *
 * A transition function can only be moved and not copied.
 * 
 **/
class TransitionFunction {
public:
  /** @brief number of states N **/
  abs_type m_no_states;
  /** @brief number of inputs M **/
  abs_type m_no_inputs;   
  /** @brief number of transitions T **/
  abs_ptr_type m_no_transitions; 
  /** @brief array[T] containing the list of all pre */
  std::unique_ptr<abs_type[]> m_pre;         
  /** @brief array[N*M] containing the pre's address in the array m_pre[T] **/
  std::unique_ptr<abs_ptr_type[]> m_pre_ptr;    
  /** @brief array[N*M] saving the number of pre for each state-input pair (i,j) **/
  std::unique_ptr<abs_type[]> m_no_pre;    
  /** @brief array[N*M] saving the number of post for each state-input pair (i,j) **/
  std::unique_ptr<abs_type[]> m_no_post;    
 
  /*difference between this and another transition class, deletion or insertion*/
  std::queue<abs_type> m_diff; 
 
  std::unique_ptr<abs_type[]> corner_IDs;
    /* is post of (i,j) out of domain ? */
  std::unique_ptr<bool[]> out_of_domain;
public:
  /* @cond  EXCLUDE from doxygen */
  /* default constructor */
  TransitionFunction() : m_no_states(0),
                         m_no_inputs(0),
                         m_no_transitions(0),
                         m_pre(nullptr),
                         m_pre_ptr(nullptr),
                         m_no_pre(nullptr),
                         m_no_post(nullptr),
                         corner_IDs(nullptr),
                         out_of_domain(nullptr) { }  


  /* move constructor */
  TransitionFunction(TransitionFunction&& other) {
    *this = std::move(other);  
  }
  /* move asignement operator */
  TransitionFunction& operator=(TransitionFunction&& other) {
    m_no_states=std::move(other.m_no_states);
    m_no_inputs=std::move(other.m_no_inputs);
    m_no_transitions=std::move(other.m_no_transitions);

    m_pre=std::move(other.m_pre);
    m_pre_ptr=std::move(other.m_pre_ptr);
    m_no_pre=std::move(other.m_no_pre);
    m_no_post=std::move(other.m_no_post);
    corner_IDs=std::move(other.corner_IDs);
    out_of_domain=std::move(other.out_of_domain);
    other.m_no_states=0;
    other.m_no_inputs=0;
    other.m_no_transitions=0;

    return *this;
  }
  /* deactivate copy constructor */
  TransitionFunction(const TransitionFunction&) = delete;     
  /* deactivate copy asignement operator */
  TransitionFunction& operator=(const TransitionFunction&) = delete;
  /* @endcond */

  /** @brief number of elements of the transition relation **/
  abs_ptr_type get_no_transitions(void) const {
    return m_no_transitions;
  }
  /** @brief return list of pre associated with action j and post k **/
  std::vector<abs_type> get_pre(const abs_type& k, const abs_type& j) const {
    std::vector<abs_type> pre{};
    if(m_pre!=nullptr) {
      if(!m_no_pre[k*m_no_inputs+j]) {
        return pre;
      }
      for(abs_type v=0; v<m_no_pre[k*m_no_inputs+j]; v++) {
        pre.push_back(m_pre[m_pre_ptr[k*m_no_inputs+j]+v]);
      }
    } else {
      std::ostringstream os;
      os << "scots::TransitionFunction.hh: Unable to get post. Transition relation is empty.";
      throw std::runtime_error(os.str().c_str());
    }
    return pre;
  }
    
  /** @brief return list of post associated with action j and post i **/
  std::vector<abs_type> get_post(const abs_type& i, const abs_type& j) const {
    std::vector<abs_type> post{};
    if(m_pre!=nullptr) {
      for(abs_type k=0; k<m_no_states; k++) {
        if(m_no_pre[k*m_no_inputs+j]) {
          for(abs_type no=0; no<m_no_pre[k*m_no_inputs+j]; no++) {
            abs_ptr_type pos=m_pre_ptr[k*m_no_inputs+j]+no;
            if(m_pre[pos]==i) {
              post.push_back(k);
            }
          }
        }
      }
    } else {
      std::ostringstream os;
      os << "TransitionFunction.hh: Error: Unable to get post. Transition relation is empty, i.e.,  m_pre and post_ are nullptr.";
      throw std::runtime_error(os.str().c_str());
    }
    return post;
  }
/*function: get_difference
   * computer the difference betwen this transitions and another one.
  */
  std::queue<abs_type> get_difference(const TransitionFunction& tf_new,
                                      WinningDomain& wd){
    std::queue<abs_type> queue_diff;
    std::vector<abs_type> winning_domain = wd.get_m_winning_domain();
    std::vector<bool> in_queuediff(m_no_states, false);
    abs_type loosing = std::numeric_limits<abs_type>::max();

    std::vector<abs_type> c;

    for(abs_type i=0; i<m_no_states; i++) {
      for (abs_type j = 0; j < m_no_inputs; j++)
      {
        std::vector<abs_type>  post_1=this->get_post(i,j);
       
        std::vector<abs_type>  post_2=tf_new.get_post(i,j);    
  
        if (post_1.size()!=post_2.size())
        {
          for (std::vector<abs_type>::iterator it=post_2.begin();it!=post_2.end();++it){
            if(in_queuediff[*it]!= true){
              queue_diff.push(*it); 
              in_queuediff[*it]=true;
            }
          }
              
        }else{
          //std::sort(post_1.begin(), post_1.end());
          //std::sort(post_2.begin(), post_2.end());
        
          if (!std::equal(post_1.begin(),post_1.end(),post_2.begin()))
          {
              for (std::vector<abs_type>::iterator it=post_2.begin();it!=post_2.end();++it){
                if(in_queuediff[*it]!= true){
                   queue_diff.push(*it); 
                  in_queuediff[*it]=true;
                }
              }
          }
        }
        std::set_difference(post_1.begin(), post_1.end(), 
                         post_2.begin(), post_2.end(), std::back_inserter(c));
        if(!c.empty() && winning_domain[i]==j)
          wd.set_value(i,loosing);
        c.clear();
     }
  }

  return queue_diff;
}


  /** @brief allocate part of the sparse matrix infrastructure **/
  void init_infrastructure(const abs_type& no_state, const abs_type& no_inputs) {
    clear();
    m_no_states=no_state;
    m_no_inputs=no_inputs;

    m_pre_ptr.reset(new abs_ptr_type[no_state*no_inputs]);
    m_no_pre.reset(new abs_type[no_state*no_inputs] ());
    m_no_post.reset(new abs_type[no_state*no_inputs] ());
    /* lower-left & upper-right corners of hyper rectangle of cells that cover attainable set */
    corner_IDs.reset(new abs_type[no_state*no_inputs*2]());
    out_of_domain.reset(new bool[no_state*no_inputs]());
    
  }

  /** @brief allocate memory for pre array **/
  void init_transitions(const abs_ptr_type& no_trans) {
    m_no_transitions=no_trans;
    m_pre.reset(new abs_type[no_trans]);
  }  
  
  /** @brief clear memory of TransitionFunction (if desired) **/
  void clear() {
    m_no_states=0;
    m_no_inputs=0;
    m_no_transitions=0;

    m_pre.reset(nullptr);
    m_pre_ptr.reset(nullptr);
    m_no_pre.reset(nullptr);
    m_no_post.reset(nullptr);
    corner_IDs.reset(nullptr);
    out_of_domain.reset(nullptr);
  }
  


};

} /* end of namespace scots */
#endif /* TRANSITIONFUNCTION_HH_ */
