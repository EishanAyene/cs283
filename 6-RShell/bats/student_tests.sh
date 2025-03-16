#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Check if 'pwd' outputs the current directory" {
    run ./dsh <<EOF
pwd
exit
EOF
    [ "$status" -eq 0 ]
    [[ "${output}" == *"/"* ]] 
}


@test "Check that echo runs without errors" {
    run ./dsh <<EOF                
echo "Hello!"
EOF
    [ "$status" -eq 0 ]
}


@test "Exit command works" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}

@test "Stop server command works" {
    run ./dsh -c 127.0.0.1 <<EOF
stop-server
EOF
    [ "$status" -eq 0 ]
}