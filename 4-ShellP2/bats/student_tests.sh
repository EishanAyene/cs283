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

@test "Built-in: cd to a directory" {
    run ./dsh <<EOF
    mkdir -p /tmp/dsh-test
    cd /tmp/dsh-test
    pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "/tmp/dsh-test" ]]
}

@test "Built-in: cd with no arguments (should not change directory)" {
    initial_dir=$(pwd)
    run ./dsh <<EOF
    cd
    pwd
EOF

    [ "$status" -eq 0 ]
    [ "$output" = "$initial_dir" ]
}

@test "Built-in: cd to a non-existent directory" {
    run ./dsh <<EOF
    cd /tmp/non_existent_dir
EOF

    [ "$status" -ne 0 ]
}

@test "Built-in: exit command" {
    run ./dsh <<EOF
    exit
EOF

    [ "$status" -eq 0 ]

}

@test "External: ls command runs successfully" {
    run ./dsh <<EOF
    ls
EOF

    [ "$status" -eq 0 ]
}

@test "External: uname command returns system info" {
    run ./dsh <<EOF
    uname
EOF

    [ "$status" -eq 0 ]
}

@test "External: pwd prints working directory" {
    run ./dsh <<EOF
    pwd
EOF

    [ "$status" -eq 0 ]
}

@test "External: non-existent command returns error" {
    run ./dsh <<EOF
    nonexistentcommand
EOF

    [ "$status" -ne 0 ]
}

@test "Parsing: echo with multiple spaces" {
    run ./dsh <<EOF
    echo     test
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "test" ]]
}

@test "Parsing: echo with quoted spaces" {
    run ./dsh <<EOF
    echo "  hello    world  "
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "  hello    world  " ]]
}

@test "Parsing: command with trailing spaces" {
    run ./dsh <<EOF
    echo test
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "test" ]]
}

@test "Parsing: command with leading spaces" {
    run ./dsh <<EOF
       echo test
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "test" ]]
}
