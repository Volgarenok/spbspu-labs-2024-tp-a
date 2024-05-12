#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

namespace novikov
{
  namespace stdx
  {
    template< typename InputIt, typename OutputIt, typename UnaryPred, typename UnaryOp >
    OutputIt transform_if(InputIt begin_in, InputIt end_in, OutputIt begin_out, UnaryPred predicate, UnaryOp unary_op)
    {
      OutputIt itout = begin_out;
      for (InputIt itin = begin_in; itin != end_in; ++itin)
      {
        if (predicate(*itin))
        {
          *itout = unary_op(*itin);
          ++itout;
        }
      }
      return itout;
    }

    template< typename Container, typename UnaryPred >
    void erase_if(Container& container, UnaryPred predicate)
    {
      for (auto it = container.begin(); it != container.end();)
      {
        if (predicate(*it))
        {
          it = container.erase(it);
        }
        else
        {
          ++it;
        }
      }
    }
  }
}

#endif
