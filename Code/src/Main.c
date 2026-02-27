// Pseudocode für Main.c

Function main()
    // Initialisiere Konfigurationsstruktur
    SimulationConfig config

    PRINT "=== Parkhaus-Simulation (Teil I: Programmgerüst) ==="

    IF NOT read_and_validate_config(config)
        PRINT_ERROR "Konfiguration konnte nicht eingelesen werden."
        RETURN 1
    END IF

    // Starte die Simulation mit der geladenen Konfiguration
    run_simulation(config)

    RETURN 0
END
