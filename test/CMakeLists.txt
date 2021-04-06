set(TARGET_TESTS_NAME type_list_test)

set(TARGET_TESTS_SOURCES
    main.cpp
    TestAt.cpp
    TestBack.cpp
    TestContains.cpp
    TestCount.cpp
    TestFilter.cpp
    TestFindFirstNotOf.cpp
    TestFindFirstOf.cpp
    TestFindIf.cpp
    TestFindIfNot.cpp
    TestFindLastNotOf.cpp
    TestFindLastOf.cpp
    TestFindTemplate.cpp
    TestFlatten.cpp
    TestFront.cpp
    TestGet.cpp
    TestMaxElement.cpp
    TestMinElement.cpp
    TestInsert.cpp
    TestPopBack.cpp
    TestPopFront.cpp
    TestPushBack.cpp
    TestPushFront.cpp
    TestRemove.cpp
    TestRemoveIf.cpp
    TestReplace.cpp
    TestReplaceIf.cpp
    TestReverse.cpp
    TestSecond.cpp
    TestSort.cpp
    TestSplit.cpp
    TestTransform.cpp
    TestTypeList.cpp
    TestTypeTraits.cpp
    TestUnique.cpp
    )

add_executable(${TARGET_TESTS_NAME} ${TARGET_TESTS_SOURCES})

target_link_libraries(${TARGET_TESTS_NAME}
    PRIVATE ${TARGET_NAME}
    PRIVATE gtest_main
    )

add_test(NAME ${TARGET_TESTS_NAME} COMMAND ${TARGET_TESTS_NAME}
    --gtest_output=xml:${CMAKE_BINARY_DIR}/${TARGET_TESTS_NAME}.xml
    )
