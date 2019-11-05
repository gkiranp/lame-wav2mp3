#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include "wav2mp3.hpp"

class ThreadPoolTest : public CppUnit::TestCase { 
private:
    Utils::thread_pool *m_tp;
    std::vector<std::string> m_wavfiles;
    
public: 
    ThreadPoolTest( std::string name ) : CppUnit::TestCase( name ) 
    {
        m_tp = nullptr;
        m_wavfiles.clear();
    }
  
    void runTest() {
        CPPUNIT_ASSERT( m_tp == nullptr );
        CPPUNIT_ASSERT( m_wavfiles.empty() );
    }
};

class ParserTest : public CppUnit::TestFixture  {
private:
    //private resources
public:
  void setUp()
  {
    //Setup test case resources
  }

  void tearDown() 
  {
    //Delete test resources
  }

  void TEST1(std::string test_name)
  {
    //test 1
  }
};

int main(int argc, char **argv) 
{
    CppUnit::TestCaller<ParserTest> test1( "TEST1", 
                                             &ParserTest::TEST1, "TEST 1" );
    CppUnit::TestResult result;
    test1.run( &result );

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
