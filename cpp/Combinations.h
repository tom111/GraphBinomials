#ifndef COMBINATIONS_H
#define COMBINATIONS_H
#include <vector>
#include <iostream>

// a class to iterate through m combinations out of n
class Combinations
{
   public:
      Combinations(size_t m, size_t n) : m_(m), n_(n), done_(false)
      {
         if (m_ > n)
         {
            throw std::string("Combinations(m, n) : m must be less than or equal to n");
         }
         if (m_ == 0)
         {
            throw std::string("Combinations(m, n) : m must be greater than zero");
         }
         if (n_ == 0)
         {
            throw std::string("Combinations(m, n) : n must be greater than zero");
         }
         if (m_ <= n_)
         {
            combination_.resize(m_);
            for (size_t i = 0; i < m_; i++) combination_[i] = i;
         }
         if (m_ == n_)
         {
            done_ = true;
         }
      }

      bool next()
      {
         if (done_) return !done_;
         size_t pos = m_ - 1;
         combination_[pos]++;
         while (!done_ && combination_[pos] > (n_ - m_ + pos))
         {
            if (pos > 0)
            {
                --pos;
                combination_[pos]++;
                for (size_t i = pos + 1; i < m_; i++)
                {
                combination_[i] = combination_[i - 1] + 1;
                }
                if (combination_[0] > n_ - m_) 
                {
                    done_ = true;
                }
            }
            else
            {
                done_ = true;
            }
         }
         return !done_;
      }

      size_t operator() (size_t i) const
      {
         if (i >= combination_.size())
         {
            throw std::string("Combination::operator() : index out of range");
         }
         return combination_[i];
      }

      size_t size() const
      {
         return combination_.size();
      }

      bool done() const
      {
         return done_;
      }

      void display() const
      {
         for (size_t i = 0; i < m_; i++)
         {
            std::cout << combination_[i] << " ";
         }
         std::cout << std::endl;
      }

   private:
      size_t m_;
      size_t n_;
      bool done_;
      std::vector<size_t> combination_;
};

class KnuthCombinations
{
      // Based on Algorithm 7.2.1.2T from "7.2.1.3 GENERATING ALL COMBINATIONS" of TAOCP (Fascicle 3A)
   public:
      KnuthCombinations(size_t t, size_t n) : t_(t), n_(n), done_(false)
      {
         if (t_ > n)
         {
            throw std::string("KnuthCombinations(t, n) : t must be less than or equal to n");
         }
         if (t_ == 0)
         {
            throw std::string("KnuthCombinations(t, n) : t must be greater than zero");
         }
         if (n_ == 0)
         {
            throw std::string("KnuthCombinations(t, n) : n must be greater than zero");
         }
         c_.resize(t_ + 2);
         // Step T1. [Initialize.]
         // Note: Knuth has 1 <= j <= t, but I am using 0 <= j < t
         for (size_t j = 0; j < t_; j++) 
         {
             c_[j] = j;
         }
         c_[t_] = n_;
         c_[t_ + 1] = 0;
         j_ = t_;
         if (t_ == n_)
         {
            done_ = true;
         }
      }

   public:
      bool next()
      {
         if (done_) 
         {
            return !done_;
         }
         // Step T2. [Visit.]
         // Note: we assume any "visiting" has already been done at this point
         if (j_ > 0)
         {
            c_[j_ - 1] = j_;
            --j_;
         }
         else
         {
            // Step T3. [Easy case?]
            if (c_[0] + 1 < c_[1])
            {
               ++c_[0];
            }
            else
            {
               j_ = 2;
               // Step T4. [Find j.]
               size_t x = 0;
               bool done = false;
               while (!done)
               {
                  c_[j_ - 2] = j_ - 2;
                  x = c_[j_ - 1] + 1;
                  if (x == c_[j_]) ++j_;
                  else done = true;
               }
               // Step T5. [Done?]
               if (j_ > t_) done_ = true;
               c_[j_ - 1] = x;
               --j_;
            }
         }
         return !done_;
      }

      size_t operator() (size_t i) const
      {
         if (i >= t_)
         {
            throw std::string("KnuthCombination::operator() : index out of range");
         }
         return c_[i];
      }

      size_t size() const
      {
         return (c_.size() - 2);
      }

      bool done() const
      {
         return done_;
      }

      void display() const
      {
         for (size_t i = 0; i < t_; i++)
         {
            std::cout << c_[i] << " ";
         }
         std::cout << std::endl;
      }

   private:
      size_t t_;
      size_t n_;
      size_t j_;
      bool done_;
      std::vector<size_t> c_;
};

#endif
