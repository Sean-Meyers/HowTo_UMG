// Copyright Epic Games, Inc. All Rights Reserved.


#include "HowTo_UMGGameModeBase.h"




void AHowTo_UMGGameModeBase::BeginPlay()
{
    // Override BeginPlay()
    Super::BeginPlay();
    ChangeMenuWidget(StartingWidgetClass);
}

// Defines how to change between menus. Removes the active user widget and
// create a new widget to replace it with.
void AHowTo_UMGGameModeBase::ChangeMenuWidget(
                                      TSubclassOf<UUserWidget> NewWidgetClass)
{
    // If there is an active widget
    if (CurrentWidget != nullptr)
    {
        // Remove the active widget
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    // If a new widget class is supplied as an argument
    if (NewWidgetClass != nullptr)
    {
        // Create a new widget with the supplied class in the current world
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

        // If the widget was created succesfully
        if (CurrentWidget != nullptr)
        {
            // Display the widget on the screen
            CurrentWidget->AddToViewport();
        }
    }
}

UWidget* AHowTo_UMGGameModeBase::new_menu_widget(
                                   TSubclassOf<UUserWidget> new_widget_class,
                                                          UPanelWidget* widget)
{
    UUserWidget* current_widget = nullptr;

    // If a valid widget class was supplied
    if (new_widget_class != nullptr)
    {
        // Create the widget and add its reference to the array
        if (widget == nullptr)
        {
            current_widget = CreateWidget<UUserWidget>(GetWorld(),
                                                            new_widget_class);
            // If the widget was created successfully 
            if (current_widget != nullptr)
            {
                current_widget->AddToViewport();
            }
        }
        else
        {
            UWidget* owner = (UWidget*) widget;
            current_widget = CreateWidget<UUserWidget>(owner,
                                                            new_widget_class);
            widget->AddChild(current_widget);

            // possibly need to fix removewidget to properly remove widgets from parents instead of just viewport
        }
        active_widgets.Emplace(current_widget);
    }

    return (UWidget*) current_widget;
}

void AHowTo_UMGGameModeBase::remove_widget(UUserWidget* widget)
{
    if (widget != nullptr)
    {
        widget->RemoveFromViewport();

        active_widgets.RemoveSingle(widget);
    }
}

// Move a widget relative to another (or the same) widget.
//
// Parameters:
//      widget -- The widget to move
//      relative -- The widget who's position will be factored into the new
//                  position of the widget to move.
//                  If the relative widget has no position data, will use
//                  (0,0) instead.
//      offset -- How much to move the widget by. Added with the position
//                of relative to determine the final position of 
//                the widget.
void AHowTo_UMGGameModeBase::widget_move(UWidget* widget,
                                         UWidget* relative, FVector2D offset)
{
    // Basically what SlotAsCanvasPanelSlot, meant for blueprints
    // does, need to cast the widget to a slot so it can be
    // repositioned.

    // Debug
    //UE_LOG(LogTemp, Warning, TEXT("widget: %p\nrelative: %p"), widget, relative);

    // If the widget has a Slot
    if (widget->Slot)
    {
        // Get the widget's slot so we can access position data
        UCanvasPanelSlot* widget_slot = Cast<UCanvasPanelSlot>(widget->Slot);

        // Initialize the coordinates of the relative widget
        FVector2D relative_position = { 0, 0 };

        // If the relative widget has a Slot
        if (relative->Slot)
        {
            // Get the coordinates of the relative widget
            UCanvasPanelSlot* relative_slot
                                     = Cast<UCanvasPanelSlot>(relative->Slot);
            relative_position = relative_slot->GetPosition();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("relative: %p does not exist!"), relative);
        }
        widget_slot->SetPosition(relative_position + offset);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("widget: %p does not exist!"), widget);
    }
    // Debug
    //UE_LOG(LogTemp, Warning, TEXT("widget_slot: %p\nrelative_slot: %p"), widget_slot,  relative_slot);

    // Still need to test this and do some stuff with Blueprints, don't forget to fix remove widget.
}

FString AHowTo_UMGGameModeBase::get_address(UObject* reference)
{
    return FString::Printf(TEXT("%p"), reference);
}


