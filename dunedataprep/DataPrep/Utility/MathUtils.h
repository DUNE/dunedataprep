// MathUtils.h
// 
// Some useful functions 
// 
//
//


#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <utility>

namespace dataprep::util {

  //
  //
  template<typename T>
    std::vector<T> moving_sum( const std::vector<T> &data, size_t lag ){
    // sums of <lag> elements in a vector of size n
    //   s0 = a[0] + a[1] + ... + a[lag-1]
    //   s1 = a[lag] + a[lag+1] + ... + a[2xlag-1]
    //   ...
    // If lag > vector size n = sum of n vector elements
    // the size of the vector returned 
    // if int(n/lag) * lag < n, int(n/lag)
    // otherwise int(n/lag) + 1
    // If data is empty returns an empty vector
    std::vector<T> ms;
    auto it  = data.cbegin();
    auto end = data.cend();

    while(it < end ){
      auto nit = it + lag;
      if( nit > end ) nit = end;
      T val = std::reduce( it, nit );
      ms.push_back( val );
      it = nit;
    }

    return ms;
  }

  //
  //
  template<typename T>
    std::pair<double, double> find_mean_and_rms( const std::vector<T> &data ){
    //
    std::pair<double, double> r (0, 0);
    if( data.empty() ) return r;
    size_t n    = data.size();
    double mean = std::reduce( data.cbegin(), data.cend() )/n;
    r.first = mean;
    if( n <= 1) return r;
    std::vector<double> diffs(n);
    std::transform(data.cbegin(), data.cend(), diffs.begin(),
		   [mean](auto d){ return ((d-mean)*(d-mean)); });
    double rms = std::reduce( diffs.cbegin(), diffs.cend() );
    rms = std::sqrt( rms / (n-1) );
    r.second = rms;
    return r;
  }

  //
  //
  template<typename T>
    double find_median( const std::vector<T> &data ){
    // median depending if the vector has an even or odd size
    // C++ version using partial sorting with std::nth_element 
    // function. The nth_element shuffles values between
    // specified blocks without sorting them within each block.
    // This is somewhat more efficient than sorting the entire 
    // vector.
    
    if( data.empty() ) return 0.0;
    
    std::vector<T> tmp_data = data;
    size_t nsz   = tmp_data.size();
    size_t nhalf = nsz/2;
    std::nth_element(tmp_data.begin(), tmp_data.begin() + nhalf, tmp_data.end());
    double med = tmp_data[nhalf];
    if( nsz % 2 == 0 ){ // if median is even
      // since all values in [0, nhalf) block are < data[nhalf] 
      // after nth_element, one just looks for a max value in this sub-array
      auto it = std::max_element(tmp_data.begin(), tmp_data.begin() + nhalf);
      med = 0.5*(*it + med);
    }
    return med;
  }

  //
  // function for interquartile outlier removal
  template<typename T>
    std::vector<T> iqr_outlier_filter( const std::vector<T> &data, double scale = 1.5 ){
    // 
    // return the vector with values between
    // Q1 - scale x IQR and Q3 + scale x IQR
    // typically scale is 1.5 which corresponds to
    // dropping points beyond +/-2.7 sigma of a normal
    // distribution
    //
    auto rvec = data;
    if( data.size() <= 4 ) return rvec;

    auto const Q1 =   data.size() / 4;  // 25% quanrtile
    auto const Q3 = 3*data.size() / 4;  // 75% quanrtile
    auto sdata = data;
    std::nth_element( sdata.begin(), sdata.begin() + Q1, sdata.end() );
    std::nth_element( sdata.begin(), sdata.begin() + Q3, sdata.end() );

    auto q1 = sdata[Q1];
    auto q3 = sdata[Q3];
    double iqr = q3 - q1;
        
    if( iqr < 1.0E-4 ) return rvec;
    double ub  = q3 + scale * iqr;
    double lb  = q1 - scale * iqr;

    rvec.erase(remove_if(rvec.begin(), rvec.end(),
			 [ub, lb](auto val){ return ((val > ub) || (val < lb)); }), rvec.end());

    return rvec;
  }

  template<typename T>
    std::pair<double, double> find_mean_and_rms_iqrfiltered( const std::vector<T> &data ){
    std::vector<T> filtered_data = iqr_outlier_filter( data );
    return find_mean_and_rms( filtered_data );
  }


} // namespace



#endif
