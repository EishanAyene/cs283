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

@test "Handle empty command" {
    run ./dsh <<EOF

EOF
    [[ "$output" == *"$CMD_WARN_NO_CMD"* ]]
}


@test "Multiple pipes 'ls | grep .sh | wc -l'" {
    run ./dsh <<EOF
ls | grep .sh | wc -l
EOF
    [ "$status" -eq 0 ]
}

@test "Exit command terminates shell" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}

@test "Running a command in background" {
    run ./dsh <<EOF
sleep 2 &
EOF
    [ "$status" -eq 0 ]
}
